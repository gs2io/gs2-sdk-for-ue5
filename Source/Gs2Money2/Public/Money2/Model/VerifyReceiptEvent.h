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
    class GS2MONEY2_API FVerifyReceiptEvent final : public FGs2Object, public TSharedFromThis<FVerifyReceiptEvent>
    {
        TOptional<FString> ContentNameValue;
        TOptional<FString> PlatformValue;
        TSharedPtr<FAppleAppStoreVerifyReceiptEvent> AppleAppStoreVerifyReceiptEventValue;
        TSharedPtr<FGooglePlayVerifyReceiptEvent> GooglePlayVerifyReceiptEventValue;

    public:
        FVerifyReceiptEvent();
        FVerifyReceiptEvent(
            const FVerifyReceiptEvent& From
        );
        virtual ~FVerifyReceiptEvent() override = default;

        TSharedPtr<FVerifyReceiptEvent> WithContentName(const TOptional<FString> ContentName);
        TSharedPtr<FVerifyReceiptEvent> WithPlatform(const TOptional<FString> Platform);
        TSharedPtr<FVerifyReceiptEvent> WithAppleAppStoreVerifyReceiptEvent(const TSharedPtr<FAppleAppStoreVerifyReceiptEvent> AppleAppStoreVerifyReceiptEvent);
        TSharedPtr<FVerifyReceiptEvent> WithGooglePlayVerifyReceiptEvent(const TSharedPtr<FGooglePlayVerifyReceiptEvent> GooglePlayVerifyReceiptEvent);

        TOptional<FString> GetContentName() const;
        TOptional<FString> GetPlatform() const;
        TSharedPtr<FAppleAppStoreVerifyReceiptEvent> GetAppleAppStoreVerifyReceiptEvent() const;
        TSharedPtr<FGooglePlayVerifyReceiptEvent> GetGooglePlayVerifyReceiptEvent() const;


        static TSharedPtr<FVerifyReceiptEvent> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FVerifyReceiptEvent, ESPMode::ThreadSafe> FVerifyReceiptEventPtr;
}