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

namespace Gs2::Distributor::Request
{
    class FUpdateCurrentDistributorMasterRequest;

    class GS2DISTRIBUTOR_API FUpdateCurrentDistributorMasterRequest final : public TSharedFromThis<FUpdateCurrentDistributorMasterRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> SettingsValue;
        
    public:
        
        FUpdateCurrentDistributorMasterRequest();
        FUpdateCurrentDistributorMasterRequest(
            const FUpdateCurrentDistributorMasterRequest& From
        );
        ~FUpdateCurrentDistributorMasterRequest() = default;

        TSharedPtr<FUpdateCurrentDistributorMasterRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FUpdateCurrentDistributorMasterRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FUpdateCurrentDistributorMasterRequest> WithSettings(const TOptional<FString> Settings);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetSettings() const;

        static TSharedPtr<FUpdateCurrentDistributorMasterRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FUpdateCurrentDistributorMasterRequest, ESPMode::ThreadSafe> FUpdateCurrentDistributorMasterRequestPtr;
}