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

namespace Gs2::Gateway::Request
{
    class FSendNotificationRequest;

    class GS2GATEWAY_API FSendNotificationRequest final : public TSharedFromThis<FSendNotificationRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> SubjectValue;
        TOptional<FString> PayloadValue;
        TOptional<bool> EnableTransferMobileNotificationValue;
        TOptional<FString> SoundValue;
        TOptional<FString> TimeOffsetTokenValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FSendNotificationRequest();
        FSendNotificationRequest(
            const FSendNotificationRequest& From
        );
        ~FSendNotificationRequest() = default;

        TSharedPtr<FSendNotificationRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FSendNotificationRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FSendNotificationRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FSendNotificationRequest> WithSubject(const TOptional<FString> Subject);
        TSharedPtr<FSendNotificationRequest> WithPayload(const TOptional<FString> Payload);
        TSharedPtr<FSendNotificationRequest> WithEnableTransferMobileNotification(const TOptional<bool> EnableTransferMobileNotification);
        TSharedPtr<FSendNotificationRequest> WithSound(const TOptional<FString> Sound);
        TSharedPtr<FSendNotificationRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);
        TSharedPtr<FSendNotificationRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetSubject() const;
        TOptional<FString> GetPayload() const;
        TOptional<bool> GetEnableTransferMobileNotification() const;
        FString GetEnableTransferMobileNotificationString() const;
        TOptional<FString> GetSound() const;
        TOptional<FString> GetTimeOffsetToken() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FSendNotificationRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FSendNotificationRequest, ESPMode::ThreadSafe> FSendNotificationRequestPtr;
}