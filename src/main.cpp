#include <division.h>
#include <pqxx/pqxx>

static const char *const HEADER = "\nDivider © 2018 Monkey Claps Inc.\n\n";
static const char *const USAGE = "Usage:\n\tdivider <numerator> <denominator>\n\nDescription:\n\tComputes the result of a fractional division,\n\tand reports both the result and the remainder.\n";

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

  // INVALID STATEMENT >> SHOULD THROW!
  // std::string add_999 = "INSERT aaaa"; // throws: libc++abi.dylib: terminating with uncaught exception of type pqxx::usage_error: Attempt to commit previously aborted transaction<READ COMMITTED>
  std::string add_999 = "INSERT INTO my_test (my_num, dummy) VALUES (999, 'dummy str')"; // DOES NOT THROW ANYTHING!
  std::cout << "\n    " << add_999;
  pipeline.insert(add_999);

  pipeline.complete();
  trx.commit();
  std::cout << "\n<<< Transaction Committed Successfully!";

  return 0;
}

// int main(int argc, const char *argv[]) {
//   Fraction f;

//   std::cout << HEADER;

//   // ensure the correct number of parameters are used.
//   if (argc < 3) {
//     std::cout << USAGE;
//     return 1;
//   }

//   f.numerator = atoll(argv[1]);
//   f.denominator = atoll(argv[2]);

//   Division d = Division(f);
//   try {
//     DivisionResult r = d.divide();

//     std::cout << "Division : " << f.numerator << " / " << f.denominator << " = " << r.division << "\n";
//     std::cout << "Remainder: " << f.numerator << " % " << f.denominator << " = " << r.remainder << "\n";
//   } catch (DivisionByZero) {
//     std::cout << "Can not divide by zero, Homer. Sober up!\n";
//   }
//   return 0;
// }
