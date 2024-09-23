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
#include "../Model/BalanceParameterValueModel.h"

namespace Gs2::Enchant::Request
{
    class FCreateBalanceParameterModelMasterRequest;

    class GS2ENCHANT_API FCreateBalanceParameterModelMasterRequest final : public TSharedFromThis<FCreateBalanceParameterModelMasterRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> NameValue;
        TOptional<FString> DescriptionValue;
        TOptional<FString> MetadataValue;
        TOptional<int64> TotalValueValue;
        TOptional<FString> InitialValueStrategyValue;
        TSharedPtr<TArray<TSharedPtr<Model::FBalanceParameterValueModel>>> ParametersValue;
        
    public:
        
        FCreateBalanceParameterModelMasterRequest();
        FCreateBalanceParameterModelMasterRequest(
            const FCreateBalanceParameterModelMasterRequest& From
        );
        ~FCreateBalanceParameterModelMasterRequest() = default;

        TSharedPtr<FCreateBalanceParameterModelMasterRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FCreateBalanceParameterModelMasterRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FCreateBalanceParameterModelMasterRequest> WithName(const TOptional<FString> Name);
        TSharedPtr<FCreateBalanceParameterModelMasterRequest> WithDescription(const TOptional<FString> Description);
        TSharedPtr<FCreateBalanceParameterModelMasterRequest> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FCreateBalanceParameterModelMasterRequest> WithTotalValue(const TOptional<int64> TotalValue);
        TSharedPtr<FCreateBalanceParameterModelMasterRequest> WithInitialValueStrategy(const TOptional<FString> InitialValueStrategy);
        TSharedPtr<FCreateBalanceParameterModelMasterRequest> WithParameters(const TSharedPtr<TArray<TSharedPtr<Model::FBalanceParameterValueModel>>> Parameters);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetName() const;
        TOptional<FString> GetDescription() const;
        TOptional<FString> GetMetadata() const;
        TOptional<int64> GetTotalValue() const;
        FString GetTotalValueString() const;
        TOptional<FString> GetInitialValueStrategy() const;TSharedPtr<TArray<TSharedPtr<Model::FBalanceParameterValueModel>>> GetParameters() const;

        static TSharedPtr<FCreateBalanceParameterModelMasterRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FCreateBalanceParameterModelMasterRequest, ESPMode::ThreadSafe> FCreateBalanceParameterModelMasterRequestPtr;
}