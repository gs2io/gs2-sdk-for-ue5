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

namespace Gs2::Gateway::Model
{
    class GS2GATEWAY_API FSendNotificationEntry final : public FGs2Object, public TSharedFromThis<FSendNotificationEntry>
    {
        TOptional<FString> UserIdValue;
        TOptional<FString> IssuerValue;
        TOptional<FString> SubjectValue;
        TOptional<FString> PayloadValue;
        TOptional<bool> EnableTransferMobileNotificationValue;
        TOptional<FString> SoundValue;

    public:
        FSendNotificationEntry();
        FSendNotificationEntry(
            const FSendNotificationEntry& From
        );
        virtual ~FSendNotificationEntry() override = default;

        TSharedPtr<FSendNotificationEntry> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FSendNotificationEntry> WithIssuer(const TOptional<FString> Issuer);
        TSharedPtr<FSendNotificationEntry> WithSubject(const TOptional<FString> Subject);
        TSharedPtr<FSendNotificationEntry> WithPayload(const TOptional<FString> Payload);
        TSharedPtr<FSendNotificationEntry> WithEnableTransferMobileNotification(const TOptional<bool> EnableTransferMobileNotification);
        TSharedPtr<FSendNotificationEntry> WithSound(const TOptional<FString> Sound);

        TOptional<FString> GetUserId() const;
        TOptional<FString> GetIssuer() const;
        TOptional<FString> GetSubject() const;
        TOptional<FString> GetPayload() const;
        TOptional<bool> GetEnableTransferMobileNotification() const;
        FString GetEnableTransferMobileNotificationString() const;
        TOptional<FString> GetSound() const;


        static TSharedPtr<FSendNotificationEntry> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FSendNotificationEntry, ESPMode::ThreadSafe> FSendNotificationEntryPtr;
}