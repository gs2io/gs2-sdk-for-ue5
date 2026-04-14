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
    class FQueryFacetsRequest;

    class GS2LOG_API FQueryFacetsRequest final : public TSharedFromThis<FQueryFacetsRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<int64> BeginValue;
        TOptional<int64> EndValue;
        TOptional<FString> QueryValue;
        
    public:
        
        FQueryFacetsRequest();
        FQueryFacetsRequest(
            const FQueryFacetsRequest& From
        );
        ~FQueryFacetsRequest() = default;

        TSharedPtr<FQueryFacetsRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FQueryFacetsRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FQueryFacetsRequest> WithBegin(const TOptional<int64> Begin);
        TSharedPtr<FQueryFacetsRequest> WithEnd(const TOptional<int64> End);
        TSharedPtr<FQueryFacetsRequest> WithQuery(const TOptional<FString> Query);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<int64> GetBegin() const;
        FString GetBeginString() const;
        TOptional<int64> GetEnd() const;
        FString GetEndString() const;
        TOptional<FString> GetQuery() const;

        static TSharedPtr<FQueryFacetsRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FQueryFacetsRequest> FQueryFacetsRequestPtr;
}