/**
 *  @file
 *  @copyright defined in eos/LICENSE.txt
 */

#include <eosiolib/action.hpp>
#include "eosio.token.hpp"
#include "omes.order.hpp"
#include <eosiolib/transaction.hpp>
#include <iostream>

namespace omes {

    using eosio::print;
    using eosio::permission_level;

    void order::create( account_name user, uint64_t oid,  std::vector<order_item>  items, asset total, string memo) {
        print("user 11122register!!");
        print("asset=");
        total.print();
        print("pression=");
        total.symbol.print(true);
        print("amount");
        print(total.amount);
        print("itms=");
        for( size_t i = 0; i < items.size(); ++i ) {
            print("xxxxxxxx");
            print(items[i].sku, ", ");
            items[i].sub_total.print();
        }

        //print(eosio::name {user});
        //account_name openmarket = N(openmarket);
        print("asset!!=");
        //print(eosio::name {openmarket});
        //auto free_coin = asset {1000, S(4, OMC)};
        //transfer(openmarket, user, free_coin, "Free Coin Drop");

        //users users( _self, user);
        orderTable ot (_self, user);
        auto existing = ot.find( oid );
        if( existing != ot.end() ) {
           print ("order found!!!");
        }
        else {
            print ("order not found");
            //first parameter of emplace is the payer
            ot.emplace( _self, [&]( auto& o ) {
               print("totalccc", total.symbol.name());
               print("total", total.amount);
               o.order_id = oid;
               o.items = items;
               o.total = total;
               o.memo = memo;
            });
            //Need to transfer some tokens to new user
            //INLINE_ACTION_SENDER(eosio::token, issue)( N(eosio.token), {N(omes.token),N(airdrop)},
            //                     { user, asset(10000, S(4, OMES)), std::string("bid name ") } );
        }
    }

    void order::hello (account_name user, string memo) {
        print(eosio::name {user});
        print("hello=========", memo);
        greetingTable gt (_self, _self);
        auto existing = gt.find( user);
        if( existing != gt.end() ) {
            print ("order found!!!");
            gt.modify( existing, _self, [&]( auto& g ) {
                g.memo = memo;
            });
        }
        else {
            print ("order not found");
            //first parameter of emplace is the payer
            gt.emplace( _self, [&]( auto& g ) {
               g.user = user;
               g.memo = memo;
            });
            //Need to transfer some tokens to new user
            //INLINE_ACTION_SENDER(eosio::token, issue)( N(eosio.token), {N(omes.token),N(airdrop)},
            //                     { user, asset(10000, S(4, OMES)), std::string("bid name ") } );
        }

        //eosio_assert( 0 , "order::hello called");
        //print("=====", memo);
    }
    void order::delay( account_name user, string memo) {
        print(eosio::name {user});
        print("=====33333", memo);
        eosio::transaction out;
        out.actions.emplace_back( permission_level{_self, N(active) }, _self, N(hello), greeting{.user = user, .memo=memo} );
        out.delay_sec = 1;
        // cancel_deferred( from ); // TODO: Remove this line when replacing deferred trxs is fixed
        out.send( _self, _self, true );

    }
} 

EOSIO_ABI( omes::order, (create)(hello)(delay))