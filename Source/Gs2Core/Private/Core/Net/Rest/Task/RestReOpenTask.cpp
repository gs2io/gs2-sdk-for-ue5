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


#include "Core/Net/Rest/Task/RestReOpenTask.h"

#include "HttpManager.h"
#include "HttpModule.h"
#include "Core/Gs2Constant.h"
#include "Core/Model/Gs2Error.h"

#include "Interfaces/IHttpResponse.h"

namespace Gs2::Core::Net::Rest::Task
{
    FRestReOpenTask::FRestReOpenTask(const FGs2RestSessionPtr Session): Session(Session)
    {

    }

    FRestReOpenTask::~FRestReOpenTask()
    {
    }

    Model::FGs2ErrorPtr FRestReOpenTask::Action(TSharedPtr<TSharedPtr<Result::FReOpenTaskResult>> Result)
    {
        auto Processing = true;
        int32 ResponseCode;
        FString ResponseBody;
        {
            auto Request = FHttpModule::Get().CreateRequest();
            Request->OnProcessRequestComplete().BindLambda(
                [&Processing, &ResponseCode, &ResponseBody](FHttpRequestPtr Request, FHttpResponsePtr Response, bool Successful)
                {
                    if (Successful) {
                        ResponseCode = Response->GetResponseCode();
                        ResponseBody = Response->GetContentAsString();
                    } else {
                        ResponseCode = 999;
                    }
                    Processing = false;
                }
            );
            const auto Url = FGs2Constant::EndpointHost
                             .Replace(TEXT("{service}"), TEXT("identifier"))
                             .Replace(TEXT("{region}"), *this->Session->RegionName())
                             .Append("/projectToken/login");
            Request->SetURL(
                Url
            );
            Request->SetVerb(TEXT("POST"));
        
            FString Body;
            const TSharedRef<TJsonWriter<TCHAR>> Writer = TJsonWriterFactory<TCHAR>::Create(&Body);
            const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
            if (Session->Credential()->ClientId() != "")
            {
                JsonRootObject->SetStringField("client_id", Session->Credential()->ClientId());
            }
            if (Session->Credential()->ClientSecret() != "")
            {
                JsonRootObject->SetStringField("client_secret", Session->Credential()->ClientSecret());
            }
            FJsonSerializer::Serialize(JsonRootObject.ToSharedRef(), Writer);
            Request->SetContentAsString(Body);
            Request->SetHeader("Content-Type", "application/json");
            Request->ProcessRequest();
            
            UE_LOG(Gs2Log, VeryVerbose, TEXT("[%s] %s %s"), TEXT("POST"), ToCStr(Url), ToCStr(Body));
        }

        if (FPlatformTLS::GetCurrentThreadId() == GGameThreadId)
        {
            FHttpModule::Get().GetHttpManager().Flush(EHttpFlushReason::FullFlush);
        }
        else
        {
            while (Processing)
            {
                FPlatformProcess::Sleep(0.01f);
            }
        }
        
        if (ResponseCode / 100 == 2)
        {
            UE_LOG(Gs2Log, Verbose, TEXT("[%d] %s"), ResponseCode, ToCStr(ResponseBody));

            TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
            if (TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(ResponseBody);
                FJsonSerializer::Deserialize(JsonReader, JsonRootObject))
            {
                const auto Token = JsonRootObject->GetStringField(ANSI_TO_TCHAR("access_token"));
                Session->Credential()->UpdateProjectToken(Token);
                Session->SetOwnerId(JsonRootObject->GetStringField(ANSI_TO_TCHAR("owner_id")));
            }
            auto Details = TArray<TSharedPtr<Model::FGs2ErrorDetail>>();
            *Result = MakeShared<Result::FReOpenTaskResult>();
            return nullptr;
        }
        return Model::FGs2Error::FromResponse(ResponseCode, ResponseBody);
    }
}
