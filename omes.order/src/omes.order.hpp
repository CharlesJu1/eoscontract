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

   class order : public contract {
      public:
         order( account_name self ):contract(self){}

      private:
          friend eosiosystem::system_contract;

          struct order_item {
            uint64_t sku;
            asset    sub_total;
            EOSLIB_SERIALIZE( order_item, (sku)(sub_total))
          };

         struct orders{
            uint64_t order_id;
            std::vector<order_item>   items; 
            asset    total;
            string   memo;

            uint64_t primary_key()const { return order_id; }
            EOSLIB_SERIALIZE( orders, (order_id)(items)(total)(memo))

          };

          struct greeting {
            account_name user;
            string memo;
            uint64_t primary_key()const { return user; }
            EOSLIB_SERIALIZE( greeting, (user)(memo))
          };

          typedef eosio::multi_index<N(orders), orders> orderTable;
          typedef eosio::multi_index<N(greeting), greeting> greetingTable;

      
      public:
          void create ( account_name user, uint64_t oid, std::vector<order_item>  items, asset total, string memo);
          void delay ( account_name user, string memo);
          void hello ( account_name user, string memo);
   };

} /// namespace openmarket
