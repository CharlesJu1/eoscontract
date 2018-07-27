/**
 *  @file
 *  @copyright defined in eos/LICENSE.txt
 */

#include <eosiolib/action.hpp>
#include "omes.product.hpp"
#include <eosiolib/transaction.hpp>
#include <iostream>

namespace omes {

    using eosio::print;
    using eosio::permission_level;

    void product::create( uint64_t sku,  asset price, string memo) {
        print("user 1112333register!!");

        //users users( _self, user);
        productTable tbl (_self, _self);
        auto existing = tbl.find( sku );
        if( existing != tbl.end() ) {
           print ("order found!!!");
        }
        else {
            print ("order not found");
            //first parameter of emplace is the payer
            tbl.emplace( _self, [&]( auto& e ) {
               e.sku = sku;
               e.price = price;
               e.memo = memo;
            });
        }
    }


    void product::update( uint64_t sku,  asset price, string memo) {
        print("prodcut update!!");

        productTable tbl (_self, _self);
        auto existing = tbl.find( sku );
        if( existing != tbl.end() ) {
           print ("product found!!!");
           tbl.modify( existing, _self, [&]( auto& e ) {
                e.sku = sku;
                e.price = price;
                e.memo = memo;
            });
        }
        else {
            print ("product not found");
        }
    }

} 

EOSIO_ABI( omes::product, (create)(update))