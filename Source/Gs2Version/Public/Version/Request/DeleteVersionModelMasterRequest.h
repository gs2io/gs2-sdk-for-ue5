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
    class FDeleteVersionModelMasterRequest;

    class GS2VERSION_API FDeleteVersionModelMasterRequest final : public TSharedFromThis<FDeleteVersionModelMasterRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> VersionNameValue;
        
    public:
        
        FDeleteVersionModelMasterRequest();
        FDeleteVersionModelMasterRequest(
            const FDeleteVersionModelMasterRequest& From
        );
        ~FDeleteVersionModelMasterRequest() = default;

        TSharedPtr<FDeleteVersionModelMasterRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FDeleteVersionModelMasterRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FDeleteVersionModelMasterRequest> WithVersionName(const TOptional<FString> VersionName);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetVersionName() const;

        static TSharedPtr<FDeleteVersionModelMasterRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDeleteVersionModelMasterRequest, ESPMode::ThreadSafe> FDeleteVersionModelMasterRequestPtr;
}