/**
 *  @file
 *  @copyright defined in eos/LICENSE.txt
 */
#pragma once

#include <eosiolib/eosio.hpp>
#include <eosiolib/asset.hpp>
#include <eosiolib/eosio.hpp>

#include <string>

namespace eosiosystem {
   class system_contract;
}

namespace omes {

   using std::string;
   using eosio::contract;
   using eosio::asset;
   using eosio::symbol_name;

   class user : public contract {
      public:
         user( account_name self ):contract(self){}

         void reguser ( account_name user);
         void signin ( account_name user);

      private:
         friend eosiosystem::system_contract;

      private:
         struct users{
            account_name username;
            uint64_t     last_signin_time = 0;

            uint64_t primary_key()const { return username; }
            EOSLIB_SERIALIZE( users, (username)(last_signin_time))

          };

          typedef eosio::multi_index<N(users), users> userTable;

   };

} /// namespace openmarket
