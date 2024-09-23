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
#include "../Model/AcquireAction.h"
#include "../Model/VerifyAction.h"
#include "../Model/ConsumeAction.h"

namespace Gs2::Exchange::Request
{
    class FUpdateRateModelMasterRequest;

    class GS2EXCHANGE_API FUpdateRateModelMasterRequest final : public TSharedFromThis<FUpdateRateModelMasterRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> RateNameValue;
        TOptional<FString> DescriptionValue;
        TOptional<FString> MetadataValue;
        TOptional<FString> TimingTypeValue;
        TOptional<int32> LockTimeValue;
        TSharedPtr<TArray<TSharedPtr<Model::FAcquireAction>>> AcquireActionsValue;
        TSharedPtr<TArray<TSharedPtr<Model::FVerifyAction>>> VerifyActionsValue;
        TSharedPtr<TArray<TSharedPtr<Model::FConsumeAction>>> ConsumeActionsValue;
        
    public:
        
        FUpdateRateModelMasterRequest();
        FUpdateRateModelMasterRequest(
            const FUpdateRateModelMasterRequest& From
        );
        ~FUpdateRateModelMasterRequest() = default;

        TSharedPtr<FUpdateRateModelMasterRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FUpdateRateModelMasterRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FUpdateRateModelMasterRequest> WithRateName(const TOptional<FString> RateName);
        TSharedPtr<FUpdateRateModelMasterRequest> WithDescription(const TOptional<FString> Description);
        TSharedPtr<FUpdateRateModelMasterRequest> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FUpdateRateModelMasterRequest> WithTimingType(const TOptional<FString> TimingType);
        TSharedPtr<FUpdateRateModelMasterRequest> WithLockTime(const TOptional<int32> LockTime);
        TSharedPtr<FUpdateRateModelMasterRequest> WithAcquireActions(const TSharedPtr<TArray<TSharedPtr<Model::FAcquireAction>>> AcquireActions);
        TSharedPtr<FUpdateRateModelMasterRequest> WithVerifyActions(const TSharedPtr<TArray<TSharedPtr<Model::FVerifyAction>>> VerifyActions);
        TSharedPtr<FUpdateRateModelMasterRequest> WithConsumeActions(const TSharedPtr<TArray<TSharedPtr<Model::FConsumeAction>>> ConsumeActions);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetRateName() const;
        TOptional<FString> GetDescription() const;
        TOptional<FString> GetMetadata() const;
        TOptional<FString> GetTimingType() const;
        TOptional<int32> GetLockTime() const;
        FString GetLockTimeString() const;TSharedPtr<TArray<TSharedPtr<Model::FAcquireAction>>> GetAcquireActions() const;TSharedPtr<TArray<TSharedPtr<Model::FVerifyAction>>> GetVerifyActions() const;TSharedPtr<TArray<TSharedPtr<Model::FConsumeAction>>> GetConsumeActions() const;

        static TSharedPtr<FUpdateRateModelMasterRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FUpdateRateModelMasterRequest, ESPMode::ThreadSafe> FUpdateRateModelMasterRequestPtr;
}