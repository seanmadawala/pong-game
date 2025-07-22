#include <allegro5/allegro.h>
#include <stdlib.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
int main(void)
{
	if(!al_init()){
		al_show_native_message_box(NULL, "Error", "Initialisation Error", "Allegro failed to initialise!", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return -1;
	}

	if(!al_install_keyboard()){
		al_show_native_message_box(NULL, "Error", "Installation Error", "Keyboard failed to install!", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return -1;
	}
	
	ALLEGRO_DISPLAY *display = al_create_display(640, 480);
	if(!display){
		al_show_native_message_box(NULL, "Error", "Initialisation Error", "Display failed to initialise!", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return -1;
	}

	ALLEGRO_TIMER *timer = al_create_timer(1.0/30.0);
	ALLEGRO_EVENT_QUEUE *queue = al_create_event_queue();
	ALLEGRO_FONT *font = al_create_builtin_font();
	if(!font){
		al_show_native_message_box(display, "Error", "Font Error", "Failed to create a font!", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		al_destroy_display(display);
		return -1;
	}
	if(!timer){
		al_show_native_message_box(display, "Error", "Timer Error", "Failed to create a timer!", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		al_destroy_display(display);
		return -1;
	}
	if(!queue){
		al_show_native_message_box(display, "Error", "Queue Error", "Failed to create an event queue!", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		al_destroy_timer(timer);
		al_destroy_display(display);
		return -1;
	}
	al_register_event_source(queue, al_get_keyboard_event_source());
	al_register_event_source(queue, al_get_timer_event_source(timer));
	al_register_event_source(queue, al_get_display_event_source(display));
	
	bool redraw = true;
	ALLEGRO_EVENT event;

	al_start_timer(timer);
	while(1){
	
		al_wait_for_event(queue, &event);
		if (event.type == ALLEGRO_EVENT_TIMER){
			redraw = true;
		}
		else if((event.type == ALLEGRO_EVENT_KEY_DOWN) || (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)){
			break;
		}

		if(redraw && al_is_event_queue_empty(queue)){
			al_clear_to_color(al_map_rgb(0, 0, 0));
			al_draw_text(font, al_map_rgb(255, 255, 255), 320, 240, ALLEGRO_ALIGN_CENTRE, "Hello, Allegro!");
			al_draw_text(font, al_map_rgb(255, 255, 255), 320, 260, ALLEGRO_ALIGN_CENTRE, "Press any key to exit.");
			al_draw_text(font, al_map_rgb(255, 255, 255), 320, 280, ALLEGRO_ALIGN_CENTRE, "Or close the window.");	
			al_flip_display();

			redraw = false;
		}
	}
	al_destroy_font(font);
	al_clear_to_color(al_map_rgb(0, 0, 0));
	al_flip_display();
	al_rest(1.0);
	al_show_native_message_box(display, "Goodbye", "Exiting", "Thank you for using this program!", NULL, ALLEGRO_MESSAGEBOX_QUESTION);
		
	al_destroy_display(display);
	al_destroy_timer(timer);
	al_destroy_event_queue(queue);

	return 0;
}
