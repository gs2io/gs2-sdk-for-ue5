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

namespace Gs2::Version::Request
{
    class FGetVersionModelRequest;

    class GS2VERSION_API FGetVersionModelRequest final : public TSharedFromThis<FGetVersionModelRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> VersionNameValue;
        
    public:
        
        FGetVersionModelRequest();
        FGetVersionModelRequest(
            const FGetVersionModelRequest& From
        );
        ~FGetVersionModelRequest() = default;

        TSharedPtr<FGetVersionModelRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FGetVersionModelRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FGetVersionModelRequest> WithVersionName(const TOptional<FString> VersionName);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetVersionName() const;

        static TSharedPtr<FGetVersionModelRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FGetVersionModelRequest, ESPMode::ThreadSafe> FGetVersionModelRequestPtr;
}