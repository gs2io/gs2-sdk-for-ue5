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

#include "Money2/Model/PlatformSetting.h"

namespace Gs2::Money2::Model
{
    FPlatformSetting::FPlatformSetting():
        AppleAppStoreValue(nullptr),
        GooglePlayValue(nullptr),
        FakeValue(nullptr)
    {
    }

    FPlatformSetting::FPlatformSetting(
        const FPlatformSetting& From
    ):
        AppleAppStoreValue(From.AppleAppStoreValue),
        GooglePlayValue(From.GooglePlayValue),
        FakeValue(From.FakeValue)
    {
    }

    TSharedPtr<FPlatformSetting> FPlatformSetting::WithAppleAppStore(
        const TSharedPtr<FAppleAppStoreSetting> AppleAppStore
    )
    {
        this->AppleAppStoreValue = AppleAppStore;
        return SharedThis(this);
    }

    TSharedPtr<FPlatformSetting> FPlatformSetting::WithGooglePlay(
        const TSharedPtr<FGooglePlaySetting> GooglePlay
    )
    {
        this->GooglePlayValue = GooglePlay;
        return SharedThis(this);
    }

    TSharedPtr<FPlatformSetting> FPlatformSetting::WithFake(
        const TSharedPtr<FFakeSetting> Fake
    )
    {
        this->FakeValue = Fake;
        return SharedThis(this);
    }
    TSharedPtr<FAppleAppStoreSetting> FPlatformSetting::GetAppleAppStore() const
    {
        return AppleAppStoreValue;
    }
    TSharedPtr<FGooglePlaySetting> FPlatformSetting::GetGooglePlay() const
    {
        return GooglePlayValue;
    }
    TSharedPtr<FFakeSetting> FPlatformSetting::GetFake() const
    {
        return FakeValue;
    }

    TSharedPtr<FPlatformSetting> FPlatformSetting::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FPlatformSetting>()
            ->WithAppleAppStore(Data->HasField(ANSI_TO_TCHAR("appleAppStore")) ? [Data]() -> Model::FAppleAppStoreSettingPtr
                {
                    if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("appleAppStore")))
                    {
                        return nullptr;
                    }
                    return Model::FAppleAppStoreSetting::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("appleAppStore")));
                 }() : nullptr)
            ->WithGooglePlay(Data->HasField(ANSI_TO_TCHAR("googlePlay")) ? [Data]() -> Model::FGooglePlaySettingPtr
                {
                    if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("googlePlay")))
                    {
                        return nullptr;
                    }
                    return Model::FGooglePlaySetting::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("googlePlay")));
                 }() : nullptr)
            ->WithFake(Data->HasField(ANSI_TO_TCHAR("fake")) ? [Data]() -> Model::FFakeSettingPtr
                {
                    if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("fake")))
                    {
                        return nullptr;
                    }
                    return Model::FFakeSetting::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("fake")));
                 }() : nullptr);
    }

    TSharedPtr<FJsonObject> FPlatformSetting::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (AppleAppStoreValue != nullptr && AppleAppStoreValue.IsValid())
        {
            JsonRootObject->SetObjectField("appleAppStore", AppleAppStoreValue->ToJson());
        }
        if (GooglePlayValue != nullptr && GooglePlayValue.IsValid())
        {
            JsonRootObject->SetObjectField("googlePlay", GooglePlayValue->ToJson());
        }
        if (FakeValue != nullptr && FakeValue.IsValid())
        {
            JsonRootObject->SetObjectField("fake", FakeValue->ToJson());
        }
        return JsonRootObject;
    }

    FString FPlatformSetting::TypeName = "PlatformSetting";
}