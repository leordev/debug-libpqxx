#include <stdlib.h>
#include <iostream>
#include <chrono>
#include <unistd.h>
#include <pqxx/pqxx>

int main(int argc, const char *argv[]) {
  std::cout << "connect to postgresql... ";
  pqxx::connection sql_connection{};
  std::cout << "connected!\n";

  while (true) {
    std::cout << "\n>>> starting sql transaction...";
    pqxx::work trx(sql_connection);
    pqxx::pipeline pipeline(trx);

    std::string create_table = "CREATE TABLE IF NOT EXISTS my_test (my_num int NOT NULL)";
    pipeline.insert(create_table);

    for (int i = 0; i < 10000; i++) {
      std::string add_123 = "INSERT INTO my_test (my_num) VALUES (123)";
      pipeline.insert(add_123);
    }
    std::cout << "\ninserting 1000 rows...";

    if (rand() % 10 < 2) {
      std::string add_999 = "INSERT INTO my_test (my_num, dummy) VALUES (999, 'dummy str')"; // DOES NOT THROW ANYTHING!
      std::cout << "\ninserting poisoned data: " << add_999;
      pipeline.insert(add_999);
    }

    pipeline.complete();
    std::cout << "\n... Pipeline completed.";

    auto start = std::chrono::steady_clock::now();
    // the pipeline will throw an exception now! :)
    while (!pipeline.empty()) pipeline.retrieve();
    auto end = std::chrono::steady_clock::now();
    std::cout << "\n+++ Pipeline cleaned in "
      << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
      << " ms";

    start = std::chrono::steady_clock::now();
    trx.commit();
    end = std::chrono::steady_clock::now();
    std::cout << "\n=== Transaction committed in "
      << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
      << " ms";
    std::cout << "\n\n";

    sleep(2);
  }

  return 0;
}
