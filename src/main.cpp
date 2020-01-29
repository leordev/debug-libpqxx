#include <iostream>
#include <pqxx/pqxx>

int main(int argc, const char *argv[]) {
  std::cout << "connect to postgresql... ";
  pqxx::connection sql_connection{};
  std::cout << "connected!\n";

  std::cout << ">>> starting sql transaction...";
  pqxx::work trx(sql_connection);
  pqxx::pipeline pipeline(trx);

  std::string create_table = "CREATE TABLE IF NOT EXISTS my_test (my_num int NOT NULL)";
  std::cout << "\n    " << create_table;
  pipeline.insert(create_table);

  std::string add_123 = "INSERT INTO my_test (my_num) VALUES (123)";
  std::cout << "\n    " << add_123;
  pipeline.insert(add_123);

  // WRONG, IT'S COMMITTING SUCCESSFULLY, EVEN THOUGH WE HAVE A SQL ERROR: column "dummy" of relation "my_test" does not exist
  std::string add_999 = "INSERT INTO my_test (my_num, dummy) VALUES (999, 'dummy str')"; // DOES NOT THROW ANYTHING!
  std::cout << "\n    " << add_999;
  pipeline.insert(add_999);

  // PS: if I do something like below, it throws CORRECTLY
  // libc++abi.dylib: terminating with uncaught exception of type pqxx::usage_error: Attempt to commit previously aborted transaction<READ COMMITTED>
  // std::string add_999 = "INSERT aaaa";

  pipeline.complete();
  trx.commit();
  std::cout << "\n<<< Transaction Committed Successfully!";

  return 0;
}
