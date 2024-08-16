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
#include "../Model/AdMob.h"
#include "../Model/UnityAd.h"
#include "../Model/AppLovinMax.h"
#include "../Model/ScriptSetting.h"
#include "../Model/NotificationSetting.h"
#include "../Model/LogSetting.h"

namespace Gs2::AdReward::Request
{
    class FCreateNamespaceRequest;

    class GS2ADREWARD_API FCreateNamespaceRequest final : public TSharedFromThis<FCreateNamespaceRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NameValue;
        TSharedPtr<Model::FAdMob> AdmobValue;
        TSharedPtr<Model::FUnityAd> UnityAdValue;
        TSharedPtr<TArray<TSharedPtr<Model::FAppLovinMax>>> AppLovinMaxesValue;
        TOptional<FString> DescriptionValue;
        TSharedPtr<Model::FScriptSetting> AcquirePointScriptValue;
        TSharedPtr<Model::FScriptSetting> ConsumePointScriptValue;
        TSharedPtr<Model::FNotificationSetting> ChangePointNotificationValue;
        TSharedPtr<Model::FLogSetting> LogSettingValue;
        
    public:
        
        FCreateNamespaceRequest();
        FCreateNamespaceRequest(
            const FCreateNamespaceRequest& From
        );
        ~FCreateNamespaceRequest() = default;

        TSharedPtr<FCreateNamespaceRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FCreateNamespaceRequest> WithName(const TOptional<FString> Name);
        TSharedPtr<FCreateNamespaceRequest> WithAdmob(const TSharedPtr<Model::FAdMob> Admob);
        TSharedPtr<FCreateNamespaceRequest> WithUnityAd(const TSharedPtr<Model::FUnityAd> UnityAd);
        TSharedPtr<FCreateNamespaceRequest> WithAppLovinMaxes(const TSharedPtr<TArray<TSharedPtr<Model::FAppLovinMax>>> AppLovinMaxes);
        TSharedPtr<FCreateNamespaceRequest> WithDescription(const TOptional<FString> Description);
        TSharedPtr<FCreateNamespaceRequest> WithAcquirePointScript(const TSharedPtr<Model::FScriptSetting> AcquirePointScript);
        TSharedPtr<FCreateNamespaceRequest> WithConsumePointScript(const TSharedPtr<Model::FScriptSetting> ConsumePointScript);
        TSharedPtr<FCreateNamespaceRequest> WithChangePointNotification(const TSharedPtr<Model::FNotificationSetting> ChangePointNotification);
        TSharedPtr<FCreateNamespaceRequest> WithLogSetting(const TSharedPtr<Model::FLogSetting> LogSetting);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetName() const;
        TSharedPtr<Model::FAdMob> GetAdmob() const;
        TSharedPtr<Model::FUnityAd> GetUnityAd() const;TSharedPtr<TArray<TSharedPtr<Model::FAppLovinMax>>> GetAppLovinMaxes() const;
        TOptional<FString> GetDescription() const;
        TSharedPtr<Model::FScriptSetting> GetAcquirePointScript() const;
        TSharedPtr<Model::FScriptSetting> GetConsumePointScript() const;
        TSharedPtr<Model::FNotificationSetting> GetChangePointNotification() const;
        TSharedPtr<Model::FLogSetting> GetLogSetting() const;

        static TSharedPtr<FCreateNamespaceRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FCreateNamespaceRequest> FCreateNamespaceRequestPtr;
}