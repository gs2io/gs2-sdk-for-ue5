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

namespace Gs2::Version::Request
{
    class FUpdateCurrentVersionMasterRequest;

    class GS2VERSION_API FUpdateCurrentVersionMasterRequest final : public TSharedFromThis<FUpdateCurrentVersionMasterRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> ModeValue;
        TOptional<FString> SettingsValue;
        TOptional<FString> UploadTokenValue;
        
    public:
        
        FUpdateCurrentVersionMasterRequest();
        FUpdateCurrentVersionMasterRequest(
            const FUpdateCurrentVersionMasterRequest& From
        );
        ~FUpdateCurrentVersionMasterRequest() = default;

        TSharedPtr<FUpdateCurrentVersionMasterRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FUpdateCurrentVersionMasterRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FUpdateCurrentVersionMasterRequest> WithMode(const TOptional<FString> Mode);
        TSharedPtr<FUpdateCurrentVersionMasterRequest> WithSettings(const TOptional<FString> Settings);
        TSharedPtr<FUpdateCurrentVersionMasterRequest> WithUploadToken(const TOptional<FString> UploadToken);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetMode() const;
        TOptional<FString> GetSettings() const;
        TOptional<FString> GetUploadToken() const;

        static TSharedPtr<FUpdateCurrentVersionMasterRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FUpdateCurrentVersionMasterRequest> FUpdateCurrentVersionMasterRequestPtr;
}