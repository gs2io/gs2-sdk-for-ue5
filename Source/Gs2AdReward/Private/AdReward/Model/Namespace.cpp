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

#include "AdReward/Model/Namespace.h"

namespace Gs2::AdReward::Model
{
    FNamespace::FNamespace():
        NamespaceIdValue(TOptional<FString>()),
        NameValue(TOptional<FString>()),
        DescriptionValue(TOptional<FString>()),
        AdmobValue(nullptr),
        UnityAdValue(nullptr),
        AppLovinMaxesValue(nullptr),
        AcquirePointScriptValue(nullptr),
        ConsumePointScriptValue(nullptr),
        ChangePointNotificationValue(nullptr),
        LogSettingValue(nullptr),
        CreatedAtValue(TOptional<int64>()),
        UpdatedAtValue(TOptional<int64>()),
        RevisionValue(TOptional<int64>())
    {
    }

    FNamespace::FNamespace(
        const FNamespace& From
    ):
        NamespaceIdValue(From.NamespaceIdValue),
        NameValue(From.NameValue),
        DescriptionValue(From.DescriptionValue),
        AdmobValue(From.AdmobValue),
        UnityAdValue(From.UnityAdValue),
        AppLovinMaxesValue(From.AppLovinMaxesValue),
        AcquirePointScriptValue(From.AcquirePointScriptValue),
        ConsumePointScriptValue(From.ConsumePointScriptValue),
        ChangePointNotificationValue(From.ChangePointNotificationValue),
        LogSettingValue(From.LogSettingValue),
        CreatedAtValue(From.CreatedAtValue),
        UpdatedAtValue(From.UpdatedAtValue),
        RevisionValue(From.RevisionValue)
    {
    }

    TSharedPtr<FNamespace> FNamespace::WithNamespaceId(
        const TOptional<FString> NamespaceId
    )
    {
        this->NamespaceIdValue = NamespaceId;
        return SharedThis(this);
    }

    TSharedPtr<FNamespace> FNamespace::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FNamespace> FNamespace::WithDescription(
        const TOptional<FString> Description
    )
    {
        this->DescriptionValue = Description;
        return SharedThis(this);
    }

    TSharedPtr<FNamespace> FNamespace::WithAdmob(
        const TSharedPtr<FAdMob> Admob
    )
    {
        this->AdmobValue = Admob;
        return SharedThis(this);
    }

    TSharedPtr<FNamespace> FNamespace::WithUnityAd(
        const TSharedPtr<FUnityAd> UnityAd
    )
    {
        this->UnityAdValue = UnityAd;
        return SharedThis(this);
    }

    TSharedPtr<FNamespace> FNamespace::WithAppLovinMaxes(
        const TSharedPtr<TArray<TSharedPtr<Model::FAppLovinMax>>> AppLovinMaxes
    )
    {
        this->AppLovinMaxesValue = AppLovinMaxes;
        return SharedThis(this);
    }

    TSharedPtr<FNamespace> FNamespace::WithAcquirePointScript(
        const TSharedPtr<FScriptSetting> AcquirePointScript
    )
    {
        this->AcquirePointScriptValue = AcquirePointScript;
        return SharedThis(this);
    }

    TSharedPtr<FNamespace> FNamespace::WithConsumePointScript(
        const TSharedPtr<FScriptSetting> ConsumePointScript
    )
    {
        this->ConsumePointScriptValue = ConsumePointScript;
        return SharedThis(this);
    }

    TSharedPtr<FNamespace> FNamespace::WithChangePointNotification(
        const TSharedPtr<FNotificationSetting> ChangePointNotification
    )
    {
        this->ChangePointNotificationValue = ChangePointNotification;
        return SharedThis(this);
    }

    TSharedPtr<FNamespace> FNamespace::WithLogSetting(
        const TSharedPtr<FLogSetting> LogSetting
    )
    {
        this->LogSettingValue = LogSetting;
        return SharedThis(this);
    }

    TSharedPtr<FNamespace> FNamespace::WithCreatedAt(
        const TOptional<int64> CreatedAt
    )
    {
        this->CreatedAtValue = CreatedAt;
        return SharedThis(this);
    }

    TSharedPtr<FNamespace> FNamespace::WithUpdatedAt(
        const TOptional<int64> UpdatedAt
    )
    {
        this->UpdatedAtValue = UpdatedAt;
        return SharedThis(this);
    }

    TSharedPtr<FNamespace> FNamespace::WithRevision(
        const TOptional<int64> Revision
    )
    {
        this->RevisionValue = Revision;
        return SharedThis(this);
    }
    TOptional<FString> FNamespace::GetNamespaceId() const
    {
        return NamespaceIdValue;
    }
    TOptional<FString> FNamespace::GetName() const
    {
        return NameValue;
    }
    TOptional<FString> FNamespace::GetDescription() const
    {
        return DescriptionValue;
    }
    TSharedPtr<FAdMob> FNamespace::GetAdmob() const
    {
        return AdmobValue;
    }
    TSharedPtr<FUnityAd> FNamespace::GetUnityAd() const
    {
        return UnityAdValue;
    }
    TSharedPtr<TArray<TSharedPtr<Model::FAppLovinMax>>> FNamespace::GetAppLovinMaxes() const
    {
        return AppLovinMaxesValue;
    }
    TSharedPtr<FScriptSetting> FNamespace::GetAcquirePointScript() const
    {
        return AcquirePointScriptValue;
    }
    TSharedPtr<FScriptSetting> FNamespace::GetConsumePointScript() const
    {
        return ConsumePointScriptValue;
    }
    TSharedPtr<FNotificationSetting> FNamespace::GetChangePointNotification() const
    {
        return ChangePointNotificationValue;
    }
    TSharedPtr<FLogSetting> FNamespace::GetLogSetting() const
    {
        return LogSettingValue;
    }
    TOptional<int64> FNamespace::GetCreatedAt() const
    {
        return CreatedAtValue;
    }

    FString FNamespace::GetCreatedAtString() const
    {
        if (!CreatedAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), CreatedAtValue.GetValue());
    }
    TOptional<int64> FNamespace::GetUpdatedAt() const
    {
        return UpdatedAtValue;
    }

    FString FNamespace::GetUpdatedAtString() const
    {
        if (!UpdatedAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), UpdatedAtValue.GetValue());
    }
    TOptional<int64> FNamespace::GetRevision() const
    {
        return RevisionValue;
    }

    FString FNamespace::GetRevisionString() const
    {
        if (!RevisionValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), RevisionValue.GetValue());
    }

    TOptional<FString> FNamespace::GetRegionFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):adReward:(?<namespaceName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(1);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FNamespace::GetOwnerIdFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):adReward:(?<namespaceName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(2);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FNamespace::GetNamespaceNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):adReward:(?<namespaceName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(3);
        }
        return TOptional<FString>();
    }

    TSharedPtr<FNamespace> FNamespace::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FNamespace>()
            ->WithNamespaceId(Data->HasField(ANSI_TO_TCHAR("namespaceId")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("namespaceId"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithName(Data->HasField(ANSI_TO_TCHAR("name")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("name"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithDescription(Data->HasField(ANSI_TO_TCHAR("description")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("description"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithAdmob(Data->HasField(ANSI_TO_TCHAR("admob")) ? [Data]() -> Model::FAdMobPtr
                {
                    if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("admob")))
                    {
                        return nullptr;
                    }
                    return Model::FAdMob::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("admob")));
                 }() : nullptr)
            ->WithUnityAd(Data->HasField(ANSI_TO_TCHAR("unityAd")) ? [Data]() -> Model::FUnityAdPtr
                {
                    if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("unityAd")))
                    {
                        return nullptr;
                    }
                    return Model::FUnityAd::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("unityAd")));
                 }() : nullptr)
            ->WithAppLovinMaxes(Data->HasField(ANSI_TO_TCHAR("appLovinMaxes")) ? [Data]() -> TSharedPtr<TArray<Model::FAppLovinMaxPtr>>
                {
                    auto v = MakeShared<TArray<Model::FAppLovinMaxPtr>>();
                    if (!Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("appLovinMaxes")) && Data->HasTypedField<EJson::Array>(ANSI_TO_TCHAR("appLovinMaxes")))
                    {
                        for (auto JsonObjectValue : Data->GetArrayField(ANSI_TO_TCHAR("appLovinMaxes")))
                        {
                            v->Add(Model::FAppLovinMax::FromJson(JsonObjectValue->AsObject()));
                        }
                    }
                    return v;
                 }() : MakeShared<TArray<Model::FAppLovinMaxPtr>>())
            ->WithAcquirePointScript(Data->HasField(ANSI_TO_TCHAR("acquirePointScript")) ? [Data]() -> Model::FScriptSettingPtr
                {
                    if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("acquirePointScript")))
                    {
                        return nullptr;
                    }
                    return Model::FScriptSetting::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("acquirePointScript")));
                 }() : nullptr)
            ->WithConsumePointScript(Data->HasField(ANSI_TO_TCHAR("consumePointScript")) ? [Data]() -> Model::FScriptSettingPtr
                {
                    if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("consumePointScript")))
                    {
                        return nullptr;
                    }
                    return Model::FScriptSetting::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("consumePointScript")));
                 }() : nullptr)
            ->WithChangePointNotification(Data->HasField(ANSI_TO_TCHAR("changePointNotification")) ? [Data]() -> Model::FNotificationSettingPtr
                {
                    if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("changePointNotification")))
                    {
                        return nullptr;
                    }
                    return Model::FNotificationSetting::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("changePointNotification")));
                 }() : nullptr)
            ->WithLogSetting(Data->HasField(ANSI_TO_TCHAR("logSetting")) ? [Data]() -> Model::FLogSettingPtr
                {
                    if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("logSetting")))
                    {
                        return nullptr;
                    }
                    return Model::FLogSetting::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("logSetting")));
                 }() : nullptr)
            ->WithCreatedAt(Data->HasField(ANSI_TO_TCHAR("createdAt")) ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("createdAt"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>())
            ->WithUpdatedAt(Data->HasField(ANSI_TO_TCHAR("updatedAt")) ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("updatedAt"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>())
            ->WithRevision(Data->HasField(ANSI_TO_TCHAR("revision")) ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("revision"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>());
    }

    TSharedPtr<FJsonObject> FNamespace::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (NamespaceIdValue.IsSet())
        {
            JsonRootObject->SetStringField("namespaceId", NamespaceIdValue.GetValue());
        }
        if (NameValue.IsSet())
        {
            JsonRootObject->SetStringField("name", NameValue.GetValue());
        }
        if (DescriptionValue.IsSet())
        {
            JsonRootObject->SetStringField("description", DescriptionValue.GetValue());
        }
        if (AdmobValue != nullptr && AdmobValue.IsValid())
        {
            JsonRootObject->SetObjectField("admob", AdmobValue->ToJson());
        }
        if (UnityAdValue != nullptr && UnityAdValue.IsValid())
        {
            JsonRootObject->SetObjectField("unityAd", UnityAdValue->ToJson());
        }
        if (AppLovinMaxesValue != nullptr && AppLovinMaxesValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *AppLovinMaxesValue)
            {
                v.Add(MakeShared<FJsonValueObject>(JsonObjectValue->ToJson()));
            }
            JsonRootObject->SetArrayField("appLovinMaxes", v);
        }
        if (AcquirePointScriptValue != nullptr && AcquirePointScriptValue.IsValid())
        {
            JsonRootObject->SetObjectField("acquirePointScript", AcquirePointScriptValue->ToJson());
        }
        if (ConsumePointScriptValue != nullptr && ConsumePointScriptValue.IsValid())
        {
            JsonRootObject->SetObjectField("consumePointScript", ConsumePointScriptValue->ToJson());
        }
        if (ChangePointNotificationValue != nullptr && ChangePointNotificationValue.IsValid())
        {
            JsonRootObject->SetObjectField("changePointNotification", ChangePointNotificationValue->ToJson());
        }
        if (LogSettingValue != nullptr && LogSettingValue.IsValid())
        {
            JsonRootObject->SetObjectField("logSetting", LogSettingValue->ToJson());
        }
        if (CreatedAtValue.IsSet())
        {
            JsonRootObject->SetStringField("createdAt", FString::Printf(TEXT("%lld"), CreatedAtValue.GetValue()));
        }
        if (UpdatedAtValue.IsSet())
        {
            JsonRootObject->SetStringField("updatedAt", FString::Printf(TEXT("%lld"), UpdatedAtValue.GetValue()));
        }
        if (RevisionValue.IsSet())
        {
            JsonRootObject->SetStringField("revision", FString::Printf(TEXT("%lld"), RevisionValue.GetValue()));
        }
        return JsonRootObject;
    }

    FString FNamespace::TypeName = "Namespace";
}