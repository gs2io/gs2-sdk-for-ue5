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
#include "../Model/BalanceParameterValueModel.h"

namespace Gs2::Enchant::Request
{
    class FUpdateBalanceParameterModelMasterRequest;

    class GS2ENCHANT_API FUpdateBalanceParameterModelMasterRequest final : public TSharedFromThis<FUpdateBalanceParameterModelMasterRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> ParameterNameValue;
        TOptional<FString> DescriptionValue;
        TOptional<FString> MetadataValue;
        TOptional<int64> TotalValueValue;
        TOptional<FString> InitialValueStrategyValue;
        TSharedPtr<TArray<TSharedPtr<Model::FBalanceParameterValueModel>>> ParametersValue;
        
    public:
        
        FUpdateBalanceParameterModelMasterRequest();
        FUpdateBalanceParameterModelMasterRequest(
            const FUpdateBalanceParameterModelMasterRequest& From
        );
        ~FUpdateBalanceParameterModelMasterRequest() = default;

        TSharedPtr<FUpdateBalanceParameterModelMasterRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FUpdateBalanceParameterModelMasterRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FUpdateBalanceParameterModelMasterRequest> WithParameterName(const TOptional<FString> ParameterName);
        TSharedPtr<FUpdateBalanceParameterModelMasterRequest> WithDescription(const TOptional<FString> Description);
        TSharedPtr<FUpdateBalanceParameterModelMasterRequest> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FUpdateBalanceParameterModelMasterRequest> WithTotalValue(const TOptional<int64> TotalValue);
        TSharedPtr<FUpdateBalanceParameterModelMasterRequest> WithInitialValueStrategy(const TOptional<FString> InitialValueStrategy);
        TSharedPtr<FUpdateBalanceParameterModelMasterRequest> WithParameters(const TSharedPtr<TArray<TSharedPtr<Model::FBalanceParameterValueModel>>> Parameters);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetParameterName() const;
        TOptional<FString> GetDescription() const;
        TOptional<FString> GetMetadata() const;
        TOptional<int64> GetTotalValue() const;
        FString GetTotalValueString() const;
        TOptional<FString> GetInitialValueStrategy() const;TSharedPtr<TArray<TSharedPtr<Model::FBalanceParameterValueModel>>> GetParameters() const;

        static TSharedPtr<FUpdateBalanceParameterModelMasterRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FUpdateBalanceParameterModelMasterRequest> FUpdateBalanceParameterModelMasterRequestPtr;
}