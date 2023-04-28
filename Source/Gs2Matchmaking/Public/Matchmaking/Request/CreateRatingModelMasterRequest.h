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

namespace Gs2::Matchmaking::Request
{
    class FCreateRatingModelMasterRequest;

    class GS2MATCHMAKING_API FCreateRatingModelMasterRequest final : public TSharedFromThis<FCreateRatingModelMasterRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> NameValue;
        TOptional<FString> DescriptionValue;
        TOptional<FString> MetadataValue;
        TOptional<int32> InitialValueValue;
        TOptional<int32> VolatilityValue;
        
    public:
        
        FCreateRatingModelMasterRequest();
        FCreateRatingModelMasterRequest(
            const FCreateRatingModelMasterRequest& From
        );
        ~FCreateRatingModelMasterRequest() = default;

        TSharedPtr<FCreateRatingModelMasterRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FCreateRatingModelMasterRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FCreateRatingModelMasterRequest> WithName(const TOptional<FString> Name);
        TSharedPtr<FCreateRatingModelMasterRequest> WithDescription(const TOptional<FString> Description);
        TSharedPtr<FCreateRatingModelMasterRequest> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FCreateRatingModelMasterRequest> WithInitialValue(const TOptional<int32> InitialValue);
        TSharedPtr<FCreateRatingModelMasterRequest> WithVolatility(const TOptional<int32> Volatility);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetName() const;
        TOptional<FString> GetDescription() const;
        TOptional<FString> GetMetadata() const;
        TOptional<int32> GetInitialValue() const;
        FString GetInitialValueString() const;
        TOptional<int32> GetVolatility() const;
        FString GetVolatilityString() const;

        static TSharedPtr<FCreateRatingModelMasterRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FCreateRatingModelMasterRequest, ESPMode::ThreadSafe> FCreateRatingModelMasterRequestPtr;
}