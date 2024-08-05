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
    class FSendInGameLogRequest;

    class GS2LOG_API FSendInGameLogRequest final : public TSharedFromThis<FSendInGameLogRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> AccessTokenValue;
        TSharedPtr<TArray<TSharedPtr<Model::FInGameLogTag>>> TagsValue;
        TOptional<FString> PayloadValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FSendInGameLogRequest();
        FSendInGameLogRequest(
            const FSendInGameLogRequest& From
        );
        ~FSendInGameLogRequest() = default;

        TSharedPtr<FSendInGameLogRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FSendInGameLogRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FSendInGameLogRequest> WithAccessToken(const TOptional<FString> AccessToken);
        TSharedPtr<FSendInGameLogRequest> WithTags(const TSharedPtr<TArray<TSharedPtr<Model::FInGameLogTag>>> Tags);
        TSharedPtr<FSendInGameLogRequest> WithPayload(const TOptional<FString> Payload);
        TSharedPtr<FSendInGameLogRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetAccessToken() const;TSharedPtr<TArray<TSharedPtr<Model::FInGameLogTag>>> GetTags() const;
        TOptional<FString> GetPayload() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FSendInGameLogRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FSendInGameLogRequest, ESPMode::ThreadSafe> FSendInGameLogRequestPtr;
}