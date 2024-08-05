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
#include "../Model/OpenIdConnectSetting.h"

namespace Gs2::Account::Request
{
    class FUpdateTakeOverTypeModelMasterRequest;

    class GS2ACCOUNT_API FUpdateTakeOverTypeModelMasterRequest final : public TSharedFromThis<FUpdateTakeOverTypeModelMasterRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<int32> TypeValue;
        TOptional<FString> DescriptionValue;
        TOptional<FString> MetadataValue;
        TSharedPtr<Model::FOpenIdConnectSetting> OpenIdConnectSettingValue;
        
    public:
        
        FUpdateTakeOverTypeModelMasterRequest();
        FUpdateTakeOverTypeModelMasterRequest(
            const FUpdateTakeOverTypeModelMasterRequest& From
        );
        ~FUpdateTakeOverTypeModelMasterRequest() = default;

        TSharedPtr<FUpdateTakeOverTypeModelMasterRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FUpdateTakeOverTypeModelMasterRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FUpdateTakeOverTypeModelMasterRequest> WithType(const TOptional<int32> Type);
        TSharedPtr<FUpdateTakeOverTypeModelMasterRequest> WithDescription(const TOptional<FString> Description);
        TSharedPtr<FUpdateTakeOverTypeModelMasterRequest> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FUpdateTakeOverTypeModelMasterRequest> WithOpenIdConnectSetting(const TSharedPtr<Model::FOpenIdConnectSetting> OpenIdConnectSetting);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<int32> GetType() const;
        FString GetTypeString() const;
        TOptional<FString> GetDescription() const;
        TOptional<FString> GetMetadata() const;
        TSharedPtr<Model::FOpenIdConnectSetting> GetOpenIdConnectSetting() const;

        static TSharedPtr<FUpdateTakeOverTypeModelMasterRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FUpdateTakeOverTypeModelMasterRequest, ESPMode::ThreadSafe> FUpdateTakeOverTypeModelMasterRequestPtr;
}