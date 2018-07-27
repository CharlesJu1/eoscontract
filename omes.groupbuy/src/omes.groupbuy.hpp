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

   class groupbuy : public contract {
      public:
         groupbuy( account_name self ):contract(self){}

      private:
          friend eosiosystem::system_contract;
          enum status : uint8_t {open, close};

          struct groupbuy_e{
            uint64_t gbid;
            uint64_t sku;
            asset    price;
            string   memo;
            uint64_t grp_size;
            std::set<account_name>   members;
            status   status;

            uint64_t primary_key()const { return gbid; }
            EOSLIB_SERIALIZE( groupbuy_e, (gbid)(sku)(price)(memo)(grp_size)(members)(status))

          };

          typedef eosio::multi_index<N(groupbuys), groupbuy_e> gbTable;
      
      public:
          void create (uint64_t gbid, uint64_t sku, asset price, string memo, uint64_t grp_size);
          void join (uint64_t gbid, account_name user);
   };

} /// namespace openmarket
