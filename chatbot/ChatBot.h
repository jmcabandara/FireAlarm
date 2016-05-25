//
//  ChatBot.h
//  chatbot
//
//  Created on 5/5/16.
//  Copyright © 2016 NobodyNada. All rights reserved.
//

#ifndef ChatBot_h
#define ChatBot_h

#include <stdio.h>
#include "ChatRoom.h"
#include "Command.h"
#include "RunningCommand.h"
#include "Filter.h"
#include "Post.h"
#include "cJSON.h"

#define REPORT_MEMORY 100

typedef enum {
    ACTION_NONE = 0,
    ACTION_STOP = 1,
    ACTION_REBOOT = 2
}StopAction;

typedef struct {
    Post *post;
    unsigned long messageID;
    int confirmation;  //-1: not confirmed, 0: false positive, 1: true positive
}Report;

typedef struct _ChatBot {
    ChatRoom *room;
    Command **commands;
    RunningCommand **runningCommands;
    size_t runningCommandCount;
    pthread_mutex_t runningCommandsLock;
    pthread_mutex_t detectorLock;
    StopAction stopAction;
    char *apiFilter;
    Filter **filters;
    unsigned filterCount;
    Report *latestReports[REPORT_MEMORY];   //index 0 is the most recent report, 1 is the second most, etc.
    int reportsWaiting; //The amount of reports that have not yet been assigned a message ID.
    int reportsUntilAnalysis;   //The number of reports left until the bot analyzes them to auto-generate filters.
}ChatBot;

ChatBot *createChatBot(ChatRoom *room, Command **commands, cJSON *latestReports, Filter **filters);
StopAction runChatBot(ChatBot *chatbot);
Post *getPostByID(ChatBot *bot, unsigned long postID);
void checkPost(ChatBot *bot, Post *post);   //This function is responsible for freeing post.
void confirmPost(ChatBot *bot, Post *post, unsigned char confirmed);
Report *reportWithMessage(ChatBot *bot, unsigned long messageID);

#endif /* ChatBot_h */