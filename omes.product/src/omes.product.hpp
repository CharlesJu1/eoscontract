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

   class product : public contract {
      public:
         product( account_name self ):contract(self){}

      private:
          friend eosiosystem::system_contract;

          struct products{
            uint64_t sku;
            asset    price;
            string   memo;

            uint64_t primary_key()const { return sku; }
            EOSLIB_SERIALIZE( products, (sku)(price)(memo))

          };

          typedef eosio::multi_index<N(products), products> productTable;
      
      public:
          void create (uint64_t sku, asset price, string memo);
          void update (uint64_t sku, asset price, string memo);
   };

} /// namespace openmarket
