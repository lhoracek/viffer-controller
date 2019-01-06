void drawDisplay(State* state, OLED &s){
   char buffer[4];
    itoa(state->rpm,buffer,10);
    //display.clear();

    display.draw_string(0,56,"RPM"); 
    display.draw_rectangle(22,56,128,63,OLED::SOLID, OLED::BLACK);
    display.draw_rectangle(22,56, 22+state->rpm/120, 63,OLED::SOLID);
    display.display();    
}
