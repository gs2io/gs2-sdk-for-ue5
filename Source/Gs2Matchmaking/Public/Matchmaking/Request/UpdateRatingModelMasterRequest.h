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

namespace Gs2::Matchmaking::Request
{
    class FUpdateRatingModelMasterRequest;

    class GS2MATCHMAKING_API FUpdateRatingModelMasterRequest final : public TSharedFromThis<FUpdateRatingModelMasterRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> RatingNameValue;
        TOptional<FString> DescriptionValue;
        TOptional<FString> MetadataValue;
        TOptional<int32> InitialValueValue;
        TOptional<int32> VolatilityValue;
        
    public:
        
        FUpdateRatingModelMasterRequest();
        FUpdateRatingModelMasterRequest(
            const FUpdateRatingModelMasterRequest& From
        );
        ~FUpdateRatingModelMasterRequest() = default;

        TSharedPtr<FUpdateRatingModelMasterRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FUpdateRatingModelMasterRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FUpdateRatingModelMasterRequest> WithRatingName(const TOptional<FString> RatingName);
        TSharedPtr<FUpdateRatingModelMasterRequest> WithDescription(const TOptional<FString> Description);
        TSharedPtr<FUpdateRatingModelMasterRequest> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FUpdateRatingModelMasterRequest> WithInitialValue(const TOptional<int32> InitialValue);
        TSharedPtr<FUpdateRatingModelMasterRequest> WithVolatility(const TOptional<int32> Volatility);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetRatingName() const;
        TOptional<FString> GetDescription() const;
        TOptional<FString> GetMetadata() const;
        TOptional<int32> GetInitialValue() const;
        FString GetInitialValueString() const;
        TOptional<int32> GetVolatility() const;
        FString GetVolatilityString() const;

        static TSharedPtr<FUpdateRatingModelMasterRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FUpdateRatingModelMasterRequest> FUpdateRatingModelMasterRequestPtr;
}