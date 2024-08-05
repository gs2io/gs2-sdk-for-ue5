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
#include "../Model/InGameLogTag.h"

namespace Gs2::Log::Request
{
    class FSendInGameLogByUserIdRequest;

    class GS2LOG_API FSendInGameLogByUserIdRequest final : public TSharedFromThis<FSendInGameLogByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> UserIdValue;
        TSharedPtr<TArray<TSharedPtr<Model::FInGameLogTag>>> TagsValue;
        TOptional<FString> PayloadValue;
        TOptional<FString> TimeOffsetTokenValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FSendInGameLogByUserIdRequest();
        FSendInGameLogByUserIdRequest(
            const FSendInGameLogByUserIdRequest& From
        );
        ~FSendInGameLogByUserIdRequest() = default;

        TSharedPtr<FSendInGameLogByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FSendInGameLogByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FSendInGameLogByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FSendInGameLogByUserIdRequest> WithTags(const TSharedPtr<TArray<TSharedPtr<Model::FInGameLogTag>>> Tags);
        TSharedPtr<FSendInGameLogByUserIdRequest> WithPayload(const TOptional<FString> Payload);
        TSharedPtr<FSendInGameLogByUserIdRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);
        TSharedPtr<FSendInGameLogByUserIdRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetUserId() const;TSharedPtr<TArray<TSharedPtr<Model::FInGameLogTag>>> GetTags() const;
        TOptional<FString> GetPayload() const;
        TOptional<FString> GetTimeOffsetToken() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FSendInGameLogByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FSendInGameLogByUserIdRequest, ESPMode::ThreadSafe> FSendInGameLogByUserIdRequestPtr;
}