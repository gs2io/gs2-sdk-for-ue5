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

namespace Gs2::Inbox::Request
{
    class FUpdateCurrentMessageMasterRequest;

    class GS2INBOX_API FUpdateCurrentMessageMasterRequest final : public TSharedFromThis<FUpdateCurrentMessageMasterRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> SettingsValue;
        
    public:
        
        FUpdateCurrentMessageMasterRequest();
        FUpdateCurrentMessageMasterRequest(
            const FUpdateCurrentMessageMasterRequest& From
        );
        ~FUpdateCurrentMessageMasterRequest() = default;

        TSharedPtr<FUpdateCurrentMessageMasterRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FUpdateCurrentMessageMasterRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FUpdateCurrentMessageMasterRequest> WithSettings(const TOptional<FString> Settings);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetSettings() const;

        static TSharedPtr<FUpdateCurrentMessageMasterRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FUpdateCurrentMessageMasterRequest, ESPMode::ThreadSafe> FUpdateCurrentMessageMasterRequestPtr;
}