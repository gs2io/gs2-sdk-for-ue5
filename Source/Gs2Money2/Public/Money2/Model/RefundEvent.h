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

#include "CoreMinimal.h"
#include "Core/Gs2Object.h"
#include "AppleAppStoreVerifyReceiptEvent.h"
#include "GooglePlayVerifyReceiptEvent.h"

namespace Gs2::Money2::Model
{
    class GS2MONEY2_API FRefundEvent final : public FGs2Object, public TSharedFromThis<FRefundEvent>
    {
        TOptional<FString> ContentNameValue;
        TOptional<FString> PlatformValue;
        TSharedPtr<FAppleAppStoreVerifyReceiptEvent> AppleAppStoreRefundEventValue;
        TSharedPtr<FGooglePlayVerifyReceiptEvent> GooglePlayRefundEventValue;

    public:
        FRefundEvent();
        FRefundEvent(
            const FRefundEvent& From
        );
        virtual ~FRefundEvent() override = default;

        TSharedPtr<FRefundEvent> WithContentName(const TOptional<FString> ContentName);
        TSharedPtr<FRefundEvent> WithPlatform(const TOptional<FString> Platform);
        TSharedPtr<FRefundEvent> WithAppleAppStoreRefundEvent(const TSharedPtr<FAppleAppStoreVerifyReceiptEvent> AppleAppStoreRefundEvent);
        TSharedPtr<FRefundEvent> WithGooglePlayRefundEvent(const TSharedPtr<FGooglePlayVerifyReceiptEvent> GooglePlayRefundEvent);

        TOptional<FString> GetContentName() const;
        TOptional<FString> GetPlatform() const;
        TSharedPtr<FAppleAppStoreVerifyReceiptEvent> GetAppleAppStoreRefundEvent() const;
        TSharedPtr<FGooglePlayVerifyReceiptEvent> GetGooglePlayRefundEvent() const;


        static TSharedPtr<FRefundEvent> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FRefundEvent, ESPMode::ThreadSafe> FRefundEventPtr;
}