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
//  PTMediaPlayerItem.h
//
//  Created by Catalin Dobre on 3/25/12.
//


#import <Foundation/Foundation.h>
#import <CoreMedia/CoreMedia.h>

@class PTMetadata;
@class PTMediaSelectionOption;
@class PTNotificationHistory;
@class PTTextStyleRule;
@protocol PTAdResolver;

extern NSString *const PTMediaPlayerItemTimeKey;
extern NSString *const PTMediaPlayerItemDateKey;
extern NSString *const PTMediaPlayerItemDurationKey;
extern NSString *const PTMediaPlayerItemSizeKey;

/**
 * PTMediaPlayerItem class represents a specific audio-video media.
 *
 */
@interface PTMediaPlayerItem : NSObject

/**
 * The URL for retrieving the media m3u8 playlist.
 */
@property (readonly, nonatomic, strong) NSURL *url;

/**
 * Media identifier.
 *
 * External services (ad resolving, ad and anc content tracking, custom CMS)
 * might use this identifier to retrieve and store information related to 
 * this media.
 */
@property (readonly, nonatomic, strong) NSString *mediaId;

/**
 * Custom metadata associated with this media item.
 */
@property (readonly, nonatomic, strong) PTMetadata *metadata;

/**
 * Specifies whether media playlist is SSL secured
 */
@property (readwrite, nonatomic) BOOL secure;

/**
 * Specifies whether the media is protected by Adobe Access DRM
 */
@property (readonly, nonatomic) BOOL isDrmProtected;

/**
 * Media player item duration.
 */
@property (readonly, nonatomic) CMTime duration;

/**
 * The current playhead time as reported by the underlying components.
 * The playhead time is calculated relative to the resolved stream, one
 * which can contain multiple ads inserted.
 */
@property (readonly, nonatomic) CMTime currentTime;

/**
 * The current playhead date as reported by the underlying component.
 *
 * The playhead date is calculated based on the current playhead time
 * and the date mapped to the starting of the segment.
 */
@property (readonly, nonatomic, strong) NSDate *currentDate;

/**
 * Native size of the media item.
 *
 * Once the playback starts, the actual size of the media will
 * be retrieved. The client can observe this property to detect
 * when the video must be scale down or up to match the desired
 * presentation size.
 */
@property (readonly, nonatomic) CGSize nativeSize;

/**
 * Native duration of media item.
 *
 * Once the playback starts, the inherent duration of the media 
 * will be retrieved. This duration does not include any additional
 * elements ( slates, ads etc) which might be inserted into the stream.
 */
@property (readonly, nonatomic) NSTimeInterval nativeDuration;

/**
 * Flag indicating if the stream is live or not.
 * Returns YES if the stream is a live stream, NO otherwise.
 * Default value = NO
 */
@property (readonly, nonatomic) BOOL isLive;

/**
 * Flag indicating that the media has multiple bit-rate profiles.
 * Returns YES if multiple profiles are available, NO otherwise.
 * Default value = NO
 */
@property (readonly, nonatomic) BOOL isDynamic;

/**
 * List of currently available bit-rates profiles for the current
 * playback window.
 */
@property (readonly, nonatomic) NSArray *profiles;

/**
 * List of currently available subtitles tracks for the current
 * stream.
 * NSArray of PTMediaSelectionOption instances
 */
@property (readonly, nonatomic) NSArray *subtitlesOptions;

/**
 * List of currently available audio tracks for the current
 * stream.
 * NSArray of PTMediaSelectionOption instances
 */
@property (readonly, nonatomic) NSArray *audioOptions;

/**
 * PTMediaSelectionOption instance of the selected preferred subtitles track option.
 * Returns nil if there is not preferred track. 
 */
@property (readonly, nonatomic) PTMediaSelectionOption *selectedSubtitleOption;

/**
 * PTMediaSelectionOption instance of the default selected alternate audio track option.
 * Returns nil if there is not preferred track.
 */
@property (readonly, nonatomic) PTMediaSelectionOption *selectedAudioOption;

/**
 * Represents text styling rules that can be applied to text in a media item.
 *
 * Use this property to format subtitles, closed captions, and other
 * text-related content of the item. The rules you specify can be applied to all
 * or part of the text in the media item.
 */
@property (nonatomic, retain) PTTextStyleRule *ccStyle;

/**
 * An instance of the PTNotificationHistory class.
 *
 * Use this property to access the list of events stored in the notification history
 * or to insert new notifications to the player items notification history.
 */
@property (nonatomic, readonly) PTNotificationHistory *notificationHistory;

/**
 * A Class following PTAdResolver protocol used for custom ad resolving.
 *
 * Use this property to define a Class that would be used for dynamically create 
 * an ad resolver.
 * The Class provided must follow the PTAdResolver protocol.
 * default Class is PTAuditudeAdResolver
 */
@property (nonatomic, assign) Class<PTAdResolver> adResolverClass;

/** @name Creating a Player Item */
/**
 * Creates a new PTMediaPlayerItem instance with specified proeprties.
 *
 * @param url The url source of the player item
 * @param mediaId The unique mediaId of the player item
 * @param metadata The PTMetadata instance describing the player item metadata
 */
- (id) initWithUrl:(NSURL *)url mediaId:(NSString *)mediaId metadata:(PTMetadata *)metadata;

/** @name Managing Media Options */
/**
 * Set a subtitles track to be displayed.
 *
 * This methods requires a PTMediaSelectionOption for the desired subtitles track.
 * Use the subtitlesOptions @property of PTMediaPlayerItem to get access to the available tracks.
 * subtitlesOptions @property is only available after the status of the player is PTMediaPlayerStatusReady.
 */
- (void)selectSubtitleOption:(PTMediaSelectionOption *)mediaSelectionOption;

/** @name Managing Playback */
/**
 * Set an alternate audio track to be played.
 *
 * This methods requires a PTMediaSelectionOption for the desired alternate audio track.
 * Use the audioOptions @property of PTMediaPlayerItem to get access to the available tracks.
 * audioOptions @property is only available after the status of the player is PTMediaPlayerStatusReady.
 */
- (void)selectAudioOption:(PTMediaSelectionOption *)mediaSelectionOption;

@end