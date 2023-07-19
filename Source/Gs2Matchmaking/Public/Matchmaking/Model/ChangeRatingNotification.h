/*
 * Copyright 2016 Game Server Services, Inc. or its affiliates. All Rights
 * Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License").
 * You may not use this file except in compliance with the License.
 * A copy of the License is located at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * or in the "license" file accompanying this file. This file is distributed
 * on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
 * express or implied. See the License for the specific language governing
 * permissions and limitations under the License.
 */

#pragma once

namespace Gs2::Matchmaking::Model
{
	class GS2MATCHMAKING_API FChangeRatingNotification : public TSharedFromThis<FChangeRatingNotification>
	{
	public:
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> RatingNameValue;
        TOptional<FString> UserIdValue;
        TOptional<float> RateValueValue;

        TSharedPtr<FChangeRatingNotification> WithNamespaceName(
            const TOptional<FString> NamespaceName
        );
        TOptional<FString> GetNamespaceName() const;

        TSharedPtr<FChangeRatingNotification> WithRatingName(
            const TOptional<FString> RatingName
        );
        TOptional<FString> GetRatingName() const;

        TSharedPtr<FChangeRatingNotification> WithUserId(
            const TOptional<FString> UserId
        );
        TOptional<FString> GetUserId() const;

        TSharedPtr<FChangeRatingNotification> WithRateValue(
            const TOptional<float> RateValue
        );
        TOptional<float> GetRateValue() const;

        static TSharedPtr<FChangeRatingNotification> FromJson(const TSharedPtr<FJsonObject> Data);
    };

    typedef TSharedPtr<FChangeRatingNotification> FChangeRatingNotificationPtr;
}
