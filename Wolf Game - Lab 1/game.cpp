#include "game.h"
#include <iostream>
#include <cmath>



playerlist::playerlist(): playercounter(0), head(nullptr) {
// constructors initialized with playercount 0 and head as null
}

playerlist::~playerlist() {
    // deallocate memory for the linked list nodes when the playerlist object is destroyed NO MEMORY LEAKS
    while (head != nullptr) {
        player* temp = head;
        head = head->next;
        delete temp;
    }
}   

void playerlist::SPAWN(double x_coord, double y_coord){ // no problems

    if ( (x_coord > 0) && (y_coord > 0)){
// create a new node, set new node the data, set the pointer to head and then set head to the pointer
        player *current = new player;
        current->x = x_coord; // data
        current->y = y_coord; // data
        current->next = head; // node pointer is head
        head = current; // head is now pointing to first node. 
        playercounter++; // update playercounter each time so that its actual value can just be called whenever
        std::cout << "success" << std::endl; 
    } 

    if ((x_coord <= 0) || (y_coord <= 0) ) {
        std::cout << "failure" << std::endl; 
    }
}

void playerlist::TIME(double time){ // range from (0,500]
// initialize temp to iterate LL with
    player *temp = head; 
    // prev to store node before
    player *prev = nullptr;

    while (temp != nullptr){ 
        double x = time*cos(atan2(temp->y,temp->x));
        double y = time*sin(atan2(temp->y,temp->x));

    // update to the negation like in the lab manual
        temp->x -= x;
        temp->y -= y; 
    
        // now check for out of bounds
        if (temp->x <= 0 || temp->y <= 0) {

            if (prev == nullptr) {// if temp is the head of the list point it to next node

                head = temp->next; // point headd to next node
                delete temp; // delete out of bounds node
                temp = head; // move to the next node
                
            } else {
                // if temp is not list head
                prev->next = temp->next;
                delete temp; // delete outn of bounds node
                temp = prev->next; // move to next node
                  // decrement playercounter
            }
            playercounter--;
        }
        else {
            // if player is in bounds, move to the next node, always need next node no matter what happens
            prev = temp;
            temp = temp->next;
        }
    }
    NUM();
}

void playerlist::LUNCH() { // no problems
    // if players are < 1, remove them, decrement # of players and remove them from linked list

    // BC: nothing in list
    if (head == nullptr) {
        NUM();
        return; // Add a return statement to exit the function if the list is empty
    } 

    // general case: node is anywhere in the list
    player *temp = head;
    player *prev = nullptr;  
// iterate linked list
    while (temp != nullptr) {
        double d = sqrt((temp->x * temp->x) + (temp->y * temp->y)); 
        if (d > 1) { // if no remove, get the next node
            prev = temp; 
            temp = temp->next;
        }
        if (d < 1) { //delete player
          //  std::cout << "eating player rn" << std::endl;
            player *invalidplayer = temp;
            
            if (prev != nullptr) { //if youre not at the head:
                prev->next = temp->next;
            
            } else {
                //std::cout << "assigning head to temp -> next" << std::endl;
                // if nothing to delete, carry on to next node, nothing to be done
                head = temp->next;
            }
            // assign temp the node after
            temp = temp->next;
            delete invalidplayer;
            playercounter--; // decrement playercounter after each decrement
        }
    }       
           NUM();

} 



void playerlist::NUM(){ // no problems
    std::cout << "num of players: " << playercounter << std::endl; 
}

void playerlist::PRT(double distance){ // range from (0,500]
    // print nodes of linked list < d 
    player *temp = head; // use temp so that head isn't being tossed around and lost in the linked list
    bool found = false; 
    // empty list check
    while ( (temp != nullptr)){
        // distance d for each point
        double d = sqrt( (temp->x * temp->x) + (temp->y * temp->y));
        // what if first valid, second not valid, third valid: then if smth is not valid, update the node and carry on!
    
        // if valid entry, then just update node and run back the loop  else, no players avaliable since everyone would have been iterated
        if ( d < distance) { 
            std::cout << temp->x << " " << temp->y << " ";// print coordinates 
            found = true; 
        } 
        // always need to go to next node no matter what happens
        temp = temp->next;
    }
    if (!found ){
        std::cout << "no players found";
    }
    
    std::cout << std::endl; 

}

void playerlist::OVER(){ //  no problems
    if ( playercounter > 0){
        std::cout << "players win" << std::endl;
    } else{
        std::cout << "wolf win" << std::endl; 
    }
    }
