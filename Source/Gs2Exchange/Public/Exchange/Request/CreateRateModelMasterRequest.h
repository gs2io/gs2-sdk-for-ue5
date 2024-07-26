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
    class FCreateRateModelMasterRequest;

    class GS2EXCHANGE_API FCreateRateModelMasterRequest final : public TSharedFromThis<FCreateRateModelMasterRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> NameValue;
        TOptional<FString> DescriptionValue;
        TOptional<FString> MetadataValue;
        TOptional<FString> TimingTypeValue;
        TOptional<int32> LockTimeValue;
        TSharedPtr<TArray<TSharedPtr<Model::FAcquireAction>>> AcquireActionsValue;
        TSharedPtr<TArray<TSharedPtr<Model::FVerifyAction>>> VerifyActionsValue;
        TSharedPtr<TArray<TSharedPtr<Model::FConsumeAction>>> ConsumeActionsValue;
        
    public:
        
        FCreateRateModelMasterRequest();
        FCreateRateModelMasterRequest(
            const FCreateRateModelMasterRequest& From
        );
        ~FCreateRateModelMasterRequest() = default;

        TSharedPtr<FCreateRateModelMasterRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FCreateRateModelMasterRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FCreateRateModelMasterRequest> WithName(const TOptional<FString> Name);
        TSharedPtr<FCreateRateModelMasterRequest> WithDescription(const TOptional<FString> Description);
        TSharedPtr<FCreateRateModelMasterRequest> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FCreateRateModelMasterRequest> WithTimingType(const TOptional<FString> TimingType);
        TSharedPtr<FCreateRateModelMasterRequest> WithLockTime(const TOptional<int32> LockTime);
        TSharedPtr<FCreateRateModelMasterRequest> WithAcquireActions(const TSharedPtr<TArray<TSharedPtr<Model::FAcquireAction>>> AcquireActions);
        TSharedPtr<FCreateRateModelMasterRequest> WithVerifyActions(const TSharedPtr<TArray<TSharedPtr<Model::FVerifyAction>>> VerifyActions);
        TSharedPtr<FCreateRateModelMasterRequest> WithConsumeActions(const TSharedPtr<TArray<TSharedPtr<Model::FConsumeAction>>> ConsumeActions);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetName() const;
        TOptional<FString> GetDescription() const;
        TOptional<FString> GetMetadata() const;
        TOptional<FString> GetTimingType() const;
        TOptional<int32> GetLockTime() const;
        FString GetLockTimeString() const;TSharedPtr<TArray<TSharedPtr<Model::FAcquireAction>>> GetAcquireActions() const;TSharedPtr<TArray<TSharedPtr<Model::FVerifyAction>>> GetVerifyActions() const;TSharedPtr<TArray<TSharedPtr<Model::FConsumeAction>>> GetConsumeActions() const;

        static TSharedPtr<FCreateRateModelMasterRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FCreateRateModelMasterRequest, ESPMode::ThreadSafe> FCreateRateModelMasterRequestPtr;
}