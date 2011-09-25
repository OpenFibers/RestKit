//
//  RKParamsAttachment.h
//  RestKit
//
//  Created by Blake Watters on 8/6/09.
//  Copyright 2009 Two Toasters
//  
//  Licensed under the Apache License, Version 2.0 (the "License");
//  you may not use this file except in compliance with the License.
//  You may obtain a copy of the License at
//  
//  http://www.apache.org/licenses/LICENSE-2.0
//  
//  Unless required by applicable law or agreed to in writing, software
//  distributed under the License is distributed on an "AS IS" BASIS,
//  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//  See the License for the specific language governing permissions and
//  limitations under the License.
//

#import <Foundation/Foundation.h>

/**
 * Models an individual part of a multi-part MIME document. These
 * attachments are stacked together within the RKParams document to
 * allow for uploading files via HTTP
 */
@interface RKParamsAttachment : NSObject {
	NSString* _name;
	NSString* _fileName;
	NSString* _MIMEType;
    NSString* _MD5;

	@private
	NSData*			_MIMEHeader;
	NSUInteger		_MIMEHeaderLength;
	NSInputStream*  _bodyStream;
	NSUInteger		_bodyLength;
	NSUInteger		_length;
	NSUInteger		_delivered;
}

/**
 * MD5 value of this attachment body
 */
@property (nonatomic, retain) NSString* MD5String;

/**
 * The parameter name of this attachment in the multi-part document
 */
@property (nonatomic, retain) NSString* name;

/**
 * The name of the attached file in the MIME stream
 * Defaults to the name of the file attached or nil if there is not one.
 */
@property (nonatomic, retain) NSString* fileName;

/**
 * The MIME type of the attached file in the MIME stream. MIME Type will be
 * auto-detected from the file extension of the attached file.
 *
 * Defaults to nil
 */
@property (nonatomic, retain) NSString* MIMEType;

/**
 * The MIME boundary string
 */
@property (nonatomic, readonly) NSString* MIMEBoundary;

/**
 * Initialize a new attachment with a given parameter name and a value
 */
- (id)initWithName:(NSString*)name value:(id<NSObject>)value;

/**
 * Initialize a new attachment with a given parameter name and the data stored in an NSData object
 */
- (id)initWithName:(NSString*)name data:(NSData*)data;

/**
 * Initialize a new attachment with a given parameter name and the data stored on disk at the given file path
 */
- (id)initWithName:(NSString*)name file:(NSString*)filePath;

/**
 * Open the attachment stream to begin reading. This will generate a MIME header and prepare the
 * attachment for writing to an RKParams stream
 */
- (void)open;

/**
 * The length of the entire attachment (including the MIME Header and the body)
 */
- (NSUInteger)length;

/**
 * Read the attachment body in a streaming fashion
 */
- (NSUInteger)read:(uint8_t *)buffer maxLength:(NSUInteger)len;

@end
