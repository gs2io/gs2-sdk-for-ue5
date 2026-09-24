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
#include "Money2/Domain/Model/Gs2Money2EzStoreContentModelDomain.h"
#include "Money2/Model/Gs2Money2AppleAppStoreContent.h"
#include "Money2/Model/Gs2Money2GooglePlayContent.h"
#include "Core/BpGs2Constant.h"
#include "Gs2Money2StoreContentModel.generated.h"

USTRUCT(BlueprintType)
struct FGs2Money2StoreContentModel
{
    GENERATED_BODY()

    Gs2::UE5::Money2::Domain::Model::FEzStoreContentModelDomainPtr Value = nullptr;
};

USTRUCT(BlueprintType)
struct FGs2Money2StoreContentModelValue
{
    GENERATED_BODY()

    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    FString Name = "";
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    FString Metadata = "";
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    FGs2Money2AppleAppStoreContent AppleAppStore = FGs2Money2AppleAppStoreContent();
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    FGs2Money2GooglePlayContent GooglePlay = FGs2Money2GooglePlayContent();
};

inline FGs2Money2StoreContentModelValue EzStoreContentModelToFGs2Money2StoreContentModelValue(
    const Gs2::UE5::Money2::Model::FEzStoreContentModelPtr Model
)
{
    FGs2Money2StoreContentModelValue Value;
    if (Model == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2Money2StoreContentModelFunctionLibrary::EzStoreContentModelToFGs2Money2StoreContentModelValue] Model parameter specification is missing."))
        return Value;
    }
    Value.Name = Model->GetName() ? *Model->GetName() : "";
    Value.Metadata = Model->GetMetadata() ? *Model->GetMetadata() : "";
    Value.AppleAppStore = Model->GetAppleAppStore() ? EzAppleAppStoreContentToFGs2Money2AppleAppStoreContent(Model->GetAppleAppStore()) : FGs2Money2AppleAppStoreContent();
    Value.GooglePlay = Model->GetGooglePlay() ? EzGooglePlayContentToFGs2Money2GooglePlayContent(Model->GetGooglePlay()) : FGs2Money2GooglePlayContent();
    return Value;
}

inline Gs2::UE5::Money2::Model::FEzStoreContentModelPtr FGs2Money2StoreContentModelValueToEzStoreContentModel(
    const FGs2Money2StoreContentModelValue Model
)
{
    return MakeShared<Gs2::UE5::Money2::Model::FEzStoreContentModel>()
        ->WithName(Model.Name)
        ->WithMetadata(Model.Metadata)
        ->WithAppleAppStore(FGs2Money2AppleAppStoreContentToEzAppleAppStoreContent(Model.AppleAppStore))
        ->WithGooglePlay(FGs2Money2GooglePlayContentToEzGooglePlayContent(Model.GooglePlay));
}

UCLASS()
class BPGS2_API UGs2Money2StoreContentModelFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()
};