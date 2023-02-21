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
    class FSendMobileNotificationByUserIdRequest;

    class GS2GATEWAY_API FSendMobileNotificationByUserIdRequest final : public TSharedFromThis<FSendMobileNotificationByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> SubjectValue;
        TOptional<FString> PayloadValue;
        TOptional<FString> SoundValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FSendMobileNotificationByUserIdRequest();
        FSendMobileNotificationByUserIdRequest(
            const FSendMobileNotificationByUserIdRequest& From
        );
        ~FSendMobileNotificationByUserIdRequest() = default;

        TSharedPtr<FSendMobileNotificationByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FSendMobileNotificationByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FSendMobileNotificationByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FSendMobileNotificationByUserIdRequest> WithSubject(const TOptional<FString> Subject);
        TSharedPtr<FSendMobileNotificationByUserIdRequest> WithPayload(const TOptional<FString> Payload);
        TSharedPtr<FSendMobileNotificationByUserIdRequest> WithSound(const TOptional<FString> Sound);
        TSharedPtr<FSendMobileNotificationByUserIdRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetSubject() const;
        TOptional<FString> GetPayload() const;
        TOptional<FString> GetSound() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FSendMobileNotificationByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FSendMobileNotificationByUserIdRequest, ESPMode::ThreadSafe> FSendMobileNotificationByUserIdRequestPtr;
}