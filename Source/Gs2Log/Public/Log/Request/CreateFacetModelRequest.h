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
    class FCreateFacetModelRequest;

    class GS2LOG_API FCreateFacetModelRequest final : public TSharedFromThis<FCreateFacetModelRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> FieldValue;
        TOptional<FString> TypeValue;
        TOptional<FString> DisplayNameValue;
        TOptional<int32> OrderValue;
        
    public:
        
        FCreateFacetModelRequest();
        FCreateFacetModelRequest(
            const FCreateFacetModelRequest& From
        );
        ~FCreateFacetModelRequest() = default;

        TSharedPtr<FCreateFacetModelRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FCreateFacetModelRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FCreateFacetModelRequest> WithField(const TOptional<FString> Field);
        TSharedPtr<FCreateFacetModelRequest> WithType(const TOptional<FString> Type);
        TSharedPtr<FCreateFacetModelRequest> WithDisplayName(const TOptional<FString> DisplayName);
        TSharedPtr<FCreateFacetModelRequest> WithOrder(const TOptional<int32> Order);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetField() const;
        TOptional<FString> GetType() const;
        TOptional<FString> GetDisplayName() const;
        TOptional<int32> GetOrder() const;
        FString GetOrderString() const;

        static TSharedPtr<FCreateFacetModelRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FCreateFacetModelRequest> FCreateFacetModelRequestPtr;
}