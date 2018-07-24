#include <eosiolib/eosio.hpp>
using namespace eosio;
class test : public eosio::contract {
public:
   using contract::contract;
   void test_action( account_name test ) {
   }
};
EOSIO_ABI( test, (test_action))
