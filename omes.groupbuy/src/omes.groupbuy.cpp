/**
 *  @file
 *  @copyright defined in eos/LICENSE.txt
 */

#include <eosiolib/action.hpp>
#include "omes.groupbuy.hpp"
#include <eosiolib/transaction.hpp>
#include <iostream>

namespace omes {

    using eosio::print;
    using eosio::permission_level;

    void groupbuy::create( uint64_t gbid, uint64_t sku,  asset price, string memo, uint64_t grp_size) {
        print("user 11111111112333register!!");

        //users users( _self, user);
        gbTable tbl (_self, _self);
        auto existing = tbl.find( gbid );
        if( existing != tbl.end() ) {
           print ("order found!!!!!");
           eosio_assert( 0, "This groupbuy already exists!" );
        }
        else {
            print ("order not found");
            //first parameter of emplace is the payer
            tbl.emplace( _self, [&]( auto& e ) {
               e.gbid = gbid;
               e.sku = sku;
               e.price = price;
               e.memo = memo;
               e.grp_size = grp_size;
               e.status = open;
            });
        }
    }

    void groupbuy::join (uint64_t gbid,  account_name user) {
        gbTable tbl (_self, _self);
        auto existing = tbl.find( gbid );
        if( existing != tbl.end() ) {
            print ("order sssssssssssfound!!!!");
            eosio_assert( existing->status == status::open, "This groupbuy is closed!" );
            tbl.modify( existing, _self, [&]( auto& e ) {
                 e.members.insert(user);
                 if (e.members.size() == e.grp_size) {
                     e.status = status::close;
                 }
            });
        }
        else {
            eosio_assert(0, "This groupbuy does not exist yet!" );
        }
    }
} 

EOSIO_ABI( omes::groupbuy, (create)(join))