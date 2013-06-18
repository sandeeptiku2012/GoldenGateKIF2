/*************************************************************************
 * ADOBE CONFIDENTIAL
 * ___________________
 *
 *  Copyright 2012 Adobe Systems Incorporated
 *  All Rights Reserved.
 *
 * NOTICE:  All information contained herein is, and remains
 * the property of Adobe Systems Incorporated and its suppliers,
 * if any.  The intellectual and technical concepts contained
 * herein are proprietary to Adobe Systems Incorporated and its
 * suppliers and are protected by all applicable intellectual property
 * laws, including trade secret and copyright laws.
 * Dissemination of this information or reproduction of this material
 * is strictly forbidden unless prior written permission is obtained
 * from Adobe Systems Incorporated.
 **************************************************************************/

//
//  PTTrackingMetadata.h
//
//  Created by Catalin Dobre on 4/8/12.
//

#import <Foundation/Foundation.h>
#import "PTMetadata.h"

extern NSString *const PTTrackingMetadataKey;

/**
 * PTTrackingMetadata class is a base class for all tracking and analytics related metadata
 */
@interface PTTrackingMetadata : PTMetadata

@end
