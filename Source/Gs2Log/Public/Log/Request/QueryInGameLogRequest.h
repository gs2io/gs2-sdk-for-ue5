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
#include "Dom/JsonObject.h"
#include "../Model/InGameLogTag.h"

namespace Gs2::Log::Request
{
    class FQueryInGameLogRequest;

    class GS2LOG_API FQueryInGameLogRequest final : public TSharedFromThis<FQueryInGameLogRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> UserIdValue;
        TSharedPtr<TArray<TSharedPtr<Model::FInGameLogTag>>> TagsValue;
        TOptional<int64> BeginValue;
        TOptional<int64> EndValue;
        TOptional<bool> LongTermValue;
        TOptional<FString> PageTokenValue;
        TOptional<int32> LimitValue;
        TOptional<FString> TimeOffsetTokenValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FQueryInGameLogRequest();
        FQueryInGameLogRequest(
            const FQueryInGameLogRequest& From
        );
        ~FQueryInGameLogRequest() = default;

        TSharedPtr<FQueryInGameLogRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FQueryInGameLogRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FQueryInGameLogRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FQueryInGameLogRequest> WithTags(const TSharedPtr<TArray<TSharedPtr<Model::FInGameLogTag>>> Tags);
        TSharedPtr<FQueryInGameLogRequest> WithBegin(const TOptional<int64> Begin);
        TSharedPtr<FQueryInGameLogRequest> WithEnd(const TOptional<int64> End);
        TSharedPtr<FQueryInGameLogRequest> WithLongTerm(const TOptional<bool> LongTerm);
        TSharedPtr<FQueryInGameLogRequest> WithPageToken(const TOptional<FString> PageToken);
        TSharedPtr<FQueryInGameLogRequest> WithLimit(const TOptional<int32> Limit);
        TSharedPtr<FQueryInGameLogRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);
        TSharedPtr<FQueryInGameLogRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetUserId() const;TSharedPtr<TArray<TSharedPtr<Model::FInGameLogTag>>> GetTags() const;
        TOptional<int64> GetBegin() const;
        FString GetBeginString() const;
        TOptional<int64> GetEnd() const;
        FString GetEndString() const;
        TOptional<bool> GetLongTerm() const;
        FString GetLongTermString() const;
        TOptional<FString> GetPageToken() const;
        TOptional<int32> GetLimit() const;
        FString GetLimitString() const;
        TOptional<FString> GetTimeOffsetToken() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FQueryInGameLogRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FQueryInGameLogRequest> FQueryInGameLogRequestPtr;
}