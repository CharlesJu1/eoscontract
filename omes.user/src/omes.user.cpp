/**
 *  @file
 *  @copyright defined in eos/LICENSE.txt
 */

#include <eosiolib/action.hpp>
#include "eosio.token.hpp"
#include "omes.user.hpp"

namespace omes {

    using eosio::print;

    void user::reguser( account_name user) {
        print("user 11122register!!");
        print(eosio::name {user});
        //account_name openmarket = N(openmarket);
        print("openmarket!!=");
        //print(eosio::name {openmarket});
        //auto free_coin = asset {1000, S(4, OMC)};
        //transfer(openmarket, user, free_coin, "Free Coin Drop");

        //users users( _self, user);
        userTable ut (_self, _self);
        auto existing = ut.find( user );
        if( existing != ut.end() ) {
           print ("user found!!!");
        }
        else {
            print ("user not found");
            //first parameter of emplace is the payer
            ut.emplace( _self, [&]( auto& u ) {
               u.username = user;
               u.last_signin_time = 100000;
            });
            //Need to transfer some tokens to new user
            INLINE_ACTION_SENDER(eosio::token, issue)( N(eosio.token), {N(omes.token),N(airdrop)},
                                 { user, asset(10000, S(4, OMES)), std::string("bid name ") } );
        }
    }

    void user::signin( account_name user) {
        print("user 11122 signin !!");
        print(eosio::name {user});
        //account_name openmarket = N(openmarket);
        print("openmarket!!=");
        //print(eosio::name {openmarket});
        //auto free_coin = asset {1000, S(4, OMC)};
        //transfer(openmarket, user, free_coin, "Free Coin Drop");

        //users users( _self, user);
        userTable ut (_self, _self);
        auto existing = ut.find( user );
        if( existing != ut.end() ) {
            print ("user found!!! last_signin_time=", existing->last_signin_time);
            print ("username=", eosio::name {existing->username});
            //if (existing->last_signin_time)
            //parameter _self is the payer
            ut.modify( existing, user, [&]( auto& u ) {
                u.username = user;
                print("last_signin_time111=", u.last_signin_time);
               // now() returns the time in seconds from 1970 of the block including this action
               u.last_signin_time = now();
               print("last_signin_time=", u.last_signin_time);
            });
            //Need to transfer some tokens to new user
            //INLINE_ACTION_SENDER(eosio::token, issue)( N(eosio.token), {N(omes.token),N(airdrop)},
            //                     { user, asset(10000, S(4, OMES)), std::string("bid name ") } );
        }
        else {
            print ("user not found");
        }
    }
} 

EOSIO_ABI( omes::user, (reguser)(signin) )