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
#include "../Model/AppleAppStoreContent.h"
#include "../Model/GooglePlayContent.h"

namespace Gs2::Money2::Request
{
    class FCreateStoreContentModelMasterRequest;

    class GS2MONEY2_API FCreateStoreContentModelMasterRequest final : public TSharedFromThis<FCreateStoreContentModelMasterRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> NameValue;
        TOptional<FString> DescriptionValue;
        TOptional<FString> MetadataValue;
        TSharedPtr<Model::FAppleAppStoreContent> AppleAppStoreValue;
        TSharedPtr<Model::FGooglePlayContent> GooglePlayValue;
        
    public:
        
        FCreateStoreContentModelMasterRequest();
        FCreateStoreContentModelMasterRequest(
            const FCreateStoreContentModelMasterRequest& From
        );
        ~FCreateStoreContentModelMasterRequest() = default;

        TSharedPtr<FCreateStoreContentModelMasterRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FCreateStoreContentModelMasterRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FCreateStoreContentModelMasterRequest> WithName(const TOptional<FString> Name);
        TSharedPtr<FCreateStoreContentModelMasterRequest> WithDescription(const TOptional<FString> Description);
        TSharedPtr<FCreateStoreContentModelMasterRequest> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FCreateStoreContentModelMasterRequest> WithAppleAppStore(const TSharedPtr<Model::FAppleAppStoreContent> AppleAppStore);
        TSharedPtr<FCreateStoreContentModelMasterRequest> WithGooglePlay(const TSharedPtr<Model::FGooglePlayContent> GooglePlay);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetName() const;
        TOptional<FString> GetDescription() const;
        TOptional<FString> GetMetadata() const;
        TSharedPtr<Model::FAppleAppStoreContent> GetAppleAppStore() const;
        TSharedPtr<Model::FGooglePlayContent> GetGooglePlay() const;

        static TSharedPtr<FCreateStoreContentModelMasterRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FCreateStoreContentModelMasterRequest, ESPMode::ThreadSafe> FCreateStoreContentModelMasterRequestPtr;
}