// 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

// 参考大话设计模式 - 访问者模式

#include <iostream>
#include <vector>
#include <cstdlib>
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <thread>


#ifndef SAFE_DELETE
#define SAFE_DELETE(p) { if(p){delete(p); (p)=NULL;} }
#endif

static const int g_item_queue_size_rel = 3;                      // 队列实际大小
static const int g_item_queue_size = g_item_queue_size_rel + 1;  // 用于判断的队列满的逻辑上限
static const int g_item_to_produce = 10;                         // 待生产数量
std::mutex g_mutex;                                              // 用于多线程同步输出，防止日志混乱

struct ItemQueue {
  int item_buffer[g_item_queue_size];  // 生产消费缓冲区，生产的数据存到此处，消费者从此处拿数据。
  size_t read_position;                // 标记位，消费者从数组中获取数据的位置
  size_t write_position;               // 标记位，生产者生产的数据放到数组中
  std::mutex queue_mtx;                // 操作缓冲区的锁，防止缓冲区数据混乱
  std::condition_variable queue_not_full;   // 条件变量，表示缓存区是否已满
  std::condition_variable queue_not_empty;  // 条件变量，表示缓冲区是否为空
} g_item_queue;


// 生成产品的实现
void ProductItem(ItemQueue* iq, int item) {
  std::unique_lock<std::mutex> queue_lock(iq->queue_mtx);
  // 判断 queue 是否已满，如果已满，则 while 等待
  while (((iq->write_position + 1) % g_item_queue_size) == iq->read_position) {
    {
      std::lock_guard<std::mutex> lock(g_mutex);
      std::cout << "缓冲区满，等待..." << std::endl;
    }
    (iq->queue_not_full).wait(queue_lock);
  }

  // queue 不为空，继续写入产品
  (iq->item_buffer)[iq->write_position] = item;

  // 写入标记位加1
  (iq->write_position)++;

  if (iq->write_position == g_item_queue_size) {
    // 已满，设定写入位置为初始位置
    iq->write_position = 0;
  }

  (iq->queue_not_empty).notify_all(); // 通知消费者，队列不为空
  queue_lock.unlock();
}

// 消费产品的实现
int ConsumeItem(ItemQueue* iq) {
  int data = -1;
  std::unique_lock<std::mutex> queue_lock(iq->queue_mtx);
  // 判断 queue 是否为空，空的时候，等待
  while (iq->read_position == iq->write_position) {
    {
      std::lock_guard<std::mutex> lock(g_mutex);
      std::cout << "缓冲区空，等待..." << std::endl;
    }
    (iq->queue_not_empty).wait(queue_lock);
  }

  data = (iq->item_buffer)[iq->read_position]; // 读取产品

  (iq->read_position)++;

  if (iq->read_position == g_item_queue_size) {
    iq->read_position = 0;
  }

  (iq->queue_not_full).notify_all();
  queue_lock.unlock();

  return data;
}

// 生产者任务
void ProducerTask() {
  for (int n = 1; n <= g_item_to_produce; n++) {
    ProductItem(&g_item_queue, n);
    {
      std::lock_guard<std::mutex> lock(g_mutex);
      std::cout << "生成产品：" << n << " " << std::endl;
    }
  }
}

void ConsumerTask() {
  static int consume_count = 0;
  while (1) {
    std::this_thread::sleep_for(std::chrono::seconds(1));
    int item = ConsumeItem(&g_item_queue);
    {
      std::lock_guard<std::mutex> lock(g_mutex);
      std::cout << "消费产品：" << item << " " << std::endl;
    }
    if (++consume_count == g_item_to_produce) {
      // 满足消费者数量后，退出
      break;
    }
  }
}

void  InitItemQueue(ItemQueue* iq) {
  iq->write_position = 0;
  iq->write_position = 0;
}

int main()
{
  InitItemQueue(&g_item_queue);
  std::thread producer_thread(ProducerTask);
  std::thread consumer_thread(ConsumerTask);

  producer_thread.join();
  consumer_thread.join();

	return 0;
}
