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
#include "Core/Gs2Object.h"
#include "AppleAppStoreContent.h"
#include "GooglePlayContent.h"

namespace Gs2::Money2::Model
{
    class GS2MONEY2_API FStoreContentModel final : public Gs2Object, public TSharedFromThis<FStoreContentModel>
    {
        TOptional<FString> StoreContentModelIdValue;
        TOptional<FString> NameValue;
        TOptional<FString> MetadataValue;
        TSharedPtr<FAppleAppStoreContent> AppleAppStoreValue;
        TSharedPtr<FGooglePlayContent> GooglePlayValue;

    public:
        FStoreContentModel();
        FStoreContentModel(
            const FStoreContentModel& From
        );
        virtual ~FStoreContentModel() override = default;

        TSharedPtr<FStoreContentModel> WithStoreContentModelId(const TOptional<FString> StoreContentModelId);
        TSharedPtr<FStoreContentModel> WithName(const TOptional<FString> Name);
        TSharedPtr<FStoreContentModel> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FStoreContentModel> WithAppleAppStore(const TSharedPtr<FAppleAppStoreContent> AppleAppStore);
        TSharedPtr<FStoreContentModel> WithGooglePlay(const TSharedPtr<FGooglePlayContent> GooglePlay);

        TOptional<FString> GetStoreContentModelId() const;
        TOptional<FString> GetName() const;
        TOptional<FString> GetMetadata() const;
        TSharedPtr<FAppleAppStoreContent> GetAppleAppStore() const;
        TSharedPtr<FGooglePlayContent> GetGooglePlay() const;

        static TOptional<FString> GetRegionFromGrn(const FString Grn);
        static TOptional<FString> GetOwnerIdFromGrn(const FString Grn);
        static TOptional<FString> GetNamespaceNameFromGrn(const FString Grn);
        static TOptional<FString> GetContentNameFromGrn(const FString Grn);

        static TSharedPtr<FStoreContentModel> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FStoreContentModel, ESPMode::ThreadSafe> FStoreContentModelPtr;
}