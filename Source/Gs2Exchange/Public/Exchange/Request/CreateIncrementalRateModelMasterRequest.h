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
#include "../Model/ConsumeAction.h"
#include "../Model/AcquireAction.h"

namespace Gs2::Exchange::Request
{
    class FCreateIncrementalRateModelMasterRequest;

    class GS2EXCHANGE_API FCreateIncrementalRateModelMasterRequest final : public TSharedFromThis<FCreateIncrementalRateModelMasterRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> NameValue;
        TOptional<FString> DescriptionValue;
        TOptional<FString> MetadataValue;
        TSharedPtr<Model::FConsumeAction> ConsumeActionValue;
        TOptional<FString> CalculateTypeValue;
        TOptional<int64> BaseValueValue;
        TOptional<int64> CoefficientValueValue;
        TOptional<FString> CalculateScriptIdValue;
        TOptional<FString> ExchangeCountIdValue;
        TSharedPtr<TArray<TSharedPtr<Model::FAcquireAction>>> AcquireActionsValue;
        
    public:
        
        FCreateIncrementalRateModelMasterRequest();
        FCreateIncrementalRateModelMasterRequest(
            const FCreateIncrementalRateModelMasterRequest& From
        );
        ~FCreateIncrementalRateModelMasterRequest() = default;

        TSharedPtr<FCreateIncrementalRateModelMasterRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FCreateIncrementalRateModelMasterRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FCreateIncrementalRateModelMasterRequest> WithName(const TOptional<FString> Name);
        TSharedPtr<FCreateIncrementalRateModelMasterRequest> WithDescription(const TOptional<FString> Description);
        TSharedPtr<FCreateIncrementalRateModelMasterRequest> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FCreateIncrementalRateModelMasterRequest> WithConsumeAction(const TSharedPtr<Model::FConsumeAction> ConsumeAction);
        TSharedPtr<FCreateIncrementalRateModelMasterRequest> WithCalculateType(const TOptional<FString> CalculateType);
        TSharedPtr<FCreateIncrementalRateModelMasterRequest> WithBaseValue(const TOptional<int64> BaseValue);
        TSharedPtr<FCreateIncrementalRateModelMasterRequest> WithCoefficientValue(const TOptional<int64> CoefficientValue);
        TSharedPtr<FCreateIncrementalRateModelMasterRequest> WithCalculateScriptId(const TOptional<FString> CalculateScriptId);
        TSharedPtr<FCreateIncrementalRateModelMasterRequest> WithExchangeCountId(const TOptional<FString> ExchangeCountId);
        TSharedPtr<FCreateIncrementalRateModelMasterRequest> WithAcquireActions(const TSharedPtr<TArray<TSharedPtr<Model::FAcquireAction>>> AcquireActions);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetName() const;
        TOptional<FString> GetDescription() const;
        TOptional<FString> GetMetadata() const;
        TSharedPtr<Model::FConsumeAction> GetConsumeAction() const;
        TOptional<FString> GetCalculateType() const;
        TOptional<int64> GetBaseValue() const;
        FString GetBaseValueString() const;
        TOptional<int64> GetCoefficientValue() const;
        FString GetCoefficientValueString() const;
        TOptional<FString> GetCalculateScriptId() const;
        TOptional<FString> GetExchangeCountId() const;TSharedPtr<TArray<TSharedPtr<Model::FAcquireAction>>> GetAcquireActions() const;

        static TSharedPtr<FCreateIncrementalRateModelMasterRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FCreateIncrementalRateModelMasterRequest, ESPMode::ThreadSafe> FCreateIncrementalRateModelMasterRequestPtr;
}