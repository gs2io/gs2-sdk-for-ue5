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

namespace Gs2::Money2::Model
{
    class GS2MONEY2_API FMobileNotificationMessage final : public FGs2Object, public TSharedFromThis<FMobileNotificationMessage>
    {
        TOptional<FString> LocaleValue;
        TOptional<FString> TitleValue;
        TOptional<FString> MessageValue;

    public:
        FMobileNotificationMessage();
        FMobileNotificationMessage(
            const FMobileNotificationMessage& From
        );
        virtual ~FMobileNotificationMessage() override = default;

        TSharedPtr<FMobileNotificationMessage> WithLocale(const TOptional<FString> Locale);
        TSharedPtr<FMobileNotificationMessage> WithTitle(const TOptional<FString> Title);
        TSharedPtr<FMobileNotificationMessage> WithMessage(const TOptional<FString> Message);

        TOptional<FString> GetLocale() const;
        TOptional<FString> GetTitle() const;
        TOptional<FString> GetMessage() const;


        static TSharedPtr<FMobileNotificationMessage> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FMobileNotificationMessage, ESPMode::ThreadSafe> FMobileNotificationMessagePtr;
}