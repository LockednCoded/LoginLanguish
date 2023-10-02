/*!
 @file main.h
 @brief main header file
 @author Jeb Nicholson
 @copyright 2023 Locked & Coded
*/

#pragma once

#include <fstream>
#include <string>
#include <iostream>
#include "preprocessor_vars.h"

#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 672

/*!
 @brief runs the webview
 @details runs the webview and calls a helper function to load html
 @return 0 if successful, 1 if failed.
*/
#ifdef _WIN32
int WINAPI WinMain(HINSTANCE /*hInst*/, HINSTANCE /*hPrevInst*/, LPSTR /*lpCmdLine*/, int /*nCmdShow*/);
#else
int main();
#endif

/*!
 @brief loads html
 @details
*/
void onDocumentLoadCallback(const std::string /*&seq*/, const std::string &req, void * /*arg*/);

// std::string dummy = R"""(
// 	{
// 	"stage": 1,
// 	"stages": [
// 		{
// 			"name": "name",
// 			"state": {
// 				"firstName": {
// 					"value": "Joe",
// 					"errors": [],
// 					"disabled": true
// 				},
// 				"lastName": {
// 					"value": "Biden",
// 					"errors": [],
// 					"disabled": true
// 				}
// 			}
// 		},
// 		{
// 			"name": "credentials",
// 			"state": {
// 				"username": {
// 					"value": "Joe52",
// 					"errors": ["Joe52 is already taken. Availiable Suggestions: \"xxXJoe_DawgXxx\", \"JoeBiden696969\", \"JoeBidenIsCool\"."],
// 					"disabled": false
// 				},
// 				"password": {
// 					"value": "",
// 					"errors": [],
// 					"disabled": false
// 				}
// 			}
// 		},
// 		{
// 			"name": "extras",
// 			"state": {
// 				"dob": {
// 					"value": "",
// 					"errors": [],
// 					"disabled": false
// 				},
// 				"tsAndCs": {
// 					"value": "false",
// 					"errors": [],
// 					"disabled": false
// 				}
// 			}
// 		},
// 		{
// 			"name": "txtcaptcha",
// 			"imageURL":"",
// 			"state": {
// 				"txtcaptcha": {
// 					"value": "",
// 					"errors": [],
// 					"disabled": false
// 				}
// 			}
// 		},
// 		{
// 			"name": "imagecaptcha",
// 			"images": [
// 				"channing/channing_tatum_4.jpg",
// 				"channing/channing_tatum_3.jpg",
// 				"bradpitt/brad_pitt_1.jpg",
// 				"channing/channing_tatum_5.jpg",
// 				"bradpitt/brad_pitt_2.jpg",
// 				"bradpitt/brad_pitt_3.jpg",
// 				"channing/channing_tatum_2.jpg",
// 				"bradpitt/brad_pitt_5.jpg",
// 				"channing/channing_tatum_1.jpg"
// 			],
// 			"challengeText":"Select 5 Channing Tatums",
// 			"state": {
// 				"selected": [1, 2, 9]
// 			}
// 		}
// 	]
// }
// )""";