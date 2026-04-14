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

namespace Gs2::Log::Request
{
    class FQueryLogRequest;

    class GS2LOG_API FQueryLogRequest final : public TSharedFromThis<FQueryLogRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<int64> BeginValue;
        TOptional<int64> EndValue;
        TOptional<FString> QueryValue;
        TOptional<FString> PageTokenValue;
        TOptional<int32> LimitValue;
        
    public:
        
        FQueryLogRequest();
        FQueryLogRequest(
            const FQueryLogRequest& From
        );
        ~FQueryLogRequest() = default;

        TSharedPtr<FQueryLogRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FQueryLogRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FQueryLogRequest> WithBegin(const TOptional<int64> Begin);
        TSharedPtr<FQueryLogRequest> WithEnd(const TOptional<int64> End);
        TSharedPtr<FQueryLogRequest> WithQuery(const TOptional<FString> Query);
        TSharedPtr<FQueryLogRequest> WithPageToken(const TOptional<FString> PageToken);
        TSharedPtr<FQueryLogRequest> WithLimit(const TOptional<int32> Limit);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<int64> GetBegin() const;
        FString GetBeginString() const;
        TOptional<int64> GetEnd() const;
        FString GetEndString() const;
        TOptional<FString> GetQuery() const;
        TOptional<FString> GetPageToken() const;
        TOptional<int32> GetLimit() const;
        FString GetLimitString() const;

        static TSharedPtr<FQueryLogRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FQueryLogRequest> FQueryLogRequestPtr;
}