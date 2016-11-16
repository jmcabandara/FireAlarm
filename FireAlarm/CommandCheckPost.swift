//
//  CommandCheckPost.swift
//  FireAlarm
//
//  Created by NobodyNada on 9/30/16.
//  Copyright © 2016 NobodyNada. All rights reserved.
//

import Foundation

class CommandCheckPost: Command {
	override class func usage() -> [String] {
		return ["check post *", "check *"]
	}
	
	override func run() throws {
		if let id = Int(arguments[0]) {
			try bot.filter.checkAndReportPost(bot.room.client.questionWithID(id))
		}
		else if let url = URL(string: arguments[0]), let id = bot.postIDFromURL(url) {
			try bot.filter.checkAndReportPost(bot.room.client.questionWithID(id))
		}
		else {
			bot.room.postReply("Please enter a valid post ID or URL.", to: message)
		}
	}
}