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
 *
 * deny overwrite
 */

#include "Datastore/Domain/Model/Gs2DatastoreEzDataObjectDomain.h"

#include "HttpManager.h"
#include "HttpModule.h"
#include "Interfaces/IHttpResponse.h"

namespace Gs2::UE5::Datastore::Domain::Model
{

    TOptional<FString> FEzDataObjectDomain::UploadUrl() const
    {
        return Domain->UploadUrl;
    }

    TOptional<FString> FEzDataObjectDomain::FileUrl() const
    {
        return Domain->FileUrl;
    }

    TOptional<int64> FEzDataObjectDomain::ContentLength() const
    {
        return Domain->ContentLength;
    }

    TOptional<FString> FEzDataObjectDomain::NextPageToken() const
    {
        return Domain->NextPageToken;
    }

    TOptional<FString> FEzDataObjectDomain::NamespaceName() const
    {
        return Domain->NamespaceName;
    }

    TOptional<FString> FEzDataObjectDomain::UserId() const
    {
        return Domain->UserId;
    }

    TOptional<FString> FEzDataObjectDomain::DataObjectName() const
    {
        return Domain->DataObjectName;
    }

    FEzDataObjectDomain::FEzDataObjectDomain(
        Gs2::Datastore::Domain::Model::FDataObjectDomainPtr Domain,
        Gs2::UE5::Util::FGs2ConnectionPtr Connection
    ): Domain(Domain), ConnectionValue(Connection) {

    }

    FEzDataObjectDomain::FPrepareDownloadByUserIdAndDataObjectNameTask::FPrepareDownloadByUserIdAndDataObjectNameTask(
        TSharedPtr<FEzDataObjectDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzDataObjectDomain::FPrepareDownloadByUserIdAndDataObjectNameTask::Action(
        TSharedPtr<TSharedPtr<Gs2::UE5::Datastore::Domain::Model::FEzDataObjectDomain>> Result
    )
    {
        const auto Future = Self->ConnectionValue->Run(
            [&]() -> Gs2::Core::Model::FGs2ErrorPtr {
                const auto Task = Self->Domain->PrepareDownloadByUserIdAndDataObjectName(
                    MakeShared<Gs2::Datastore::Request::FPrepareDownloadByUserIdAndDataObjectNameRequest>()
                );
                Task->StartSynchronousTask();
                if (Task->GetTask().IsError())
                {
                    Task->EnsureCompletion();
                    return Task->GetTask().Error();
                }
                *Result = MakeShared<Gs2::UE5::Datastore::Domain::Model::FEzDataObjectDomain>(
                    Task->GetTask().Result(),
                    Self->ConnectionValue
                );
                Task->EnsureCompletion();
                return nullptr;
            },
            nullptr
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            Future->EnsureCompletion();
            return Future->GetTask().Error();
        }
        Future->EnsureCompletion();
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FEzDataObjectDomain::FPrepareDownloadByUserIdAndDataObjectNameTask>> FEzDataObjectDomain::PrepareDownloadByUserIdAndDataObjectName(
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FPrepareDownloadByUserIdAndDataObjectNameTask>>(
            this->AsShared()
        );
    }

    Gs2::UE5::Datastore::Domain::Model::FEzDataObjectHistoryDomainPtr FEzDataObjectDomain::DataObjectHistory(
        const FString Generation
    ) const
    {
        return MakeShared<Gs2::UE5::Datastore::Domain::Model::FEzDataObjectHistoryDomain>(
            Domain->DataObjectHistory(
                Generation
            ),
            ConnectionValue
        );
    }

    FEzDataObjectDomain::FModelTask::FModelTask(
        TSharedPtr<FEzDataObjectDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzDataObjectDomain::FModelTask::Action(
        TSharedPtr<Gs2::UE5::Datastore::Model::FEzDataObjectPtr> Result
    )
    {
        const auto Future = Self->ConnectionValue->Run(
            [&]() -> Gs2::Core::Model::FGs2ErrorPtr {
                const auto Task = Self->Domain->Model();
                Task->StartSynchronousTask();
                if (Task->GetTask().IsError())
                {
                    Task->EnsureCompletion();
                    return Task->GetTask().Error();
                }
                *Result = Gs2::UE5::Datastore::Model::FEzDataObject::FromModel(Task->GetTask().Result());
                Task->EnsureCompletion();
                return nullptr;
            },
            nullptr
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            Future->EnsureCompletion();
            return Future->GetTask().Error();
        }
        Future->EnsureCompletion();
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FEzDataObjectDomain::FModelTask>> FEzDataObjectDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FEzDataObjectDomain::Subscribe(TFunction<void(Gs2::UE5::Datastore::Model::FEzDataObjectPtr)> Callback)
    {
        return Domain->Subscribe(
            [&](Gs2::Datastore::Model::FDataObjectPtr Item)
            {
                Callback(Gs2::UE5::Datastore::Model::FEzDataObject::FromModel(Item));
            }
        );
    }

    void FEzDataObjectDomain::Unsubscribe(Gs2::Core::Domain::CallbackID CallbackId)
    {
        Domain->Unsubscribe(
            CallbackId
        );
    }
    
    FEzDataObjectDomain::FDownloadTask::FDownloadTask(
        TSharedPtr<FEzDataObjectDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzDataObjectDomain::FDownloadTask::Action(
        TSharedPtr<TSharedPtr<TArray<uint8>>> Result
    )
    {
        const auto Future = Self->ConnectionValue->Run(
            [&]() -> Gs2::Core::Model::FGs2ErrorPtr {
                FString Url("");
                {
                    const auto Task = Self->Domain->PrepareDownloadByUserIdAndDataObjectName(
                        MakeShared<Gs2::Datastore::Request::FPrepareDownloadByUserIdAndDataObjectNameRequest>()
                    );
                    Task->StartSynchronousTask();
                    if (Task->GetTask().IsError())
                    {
                        Task->EnsureCompletion();
                        return Task->GetTask().Error();
                    }
                    Url = *Task->GetTask().Result()->FileUrl;
                    Task->EnsureCompletion();
                }
                {
                    auto Processing = true;
                    int32 ResponseCode;
                    TArray<uint8> ResponseBody;
                    {
                        const auto request = FHttpModule::Get().CreateRequest();
                        request->OnProcessRequestComplete().BindLambda(
                            [&Processing, &ResponseCode, &ResponseBody](FHttpRequestPtr _, FHttpResponsePtr Response, bool Successful)
                            {
                                if (Successful) {
                                    ResponseCode = Response->GetResponseCode();
                                    ResponseBody = Response->GetContent();
                                } else {
                                    ResponseCode = 999;
                                }
                                Processing = false;
                            }
                        );
                        request->SetURL(Url);

                        request->SetVerb(TEXT("GET"));

                        request->ProcessRequest();
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

                    if (ResponseCode / 100 != 2)
                        
                    {
                        const auto Details = MakeShared<TArray<TSharedPtr<Gs2::Core::Model::FGs2ErrorDetail>>>();
                        return MakeShared<Gs2::Core::Model::FUnknownError>(Details);
                    }

                    const auto Value = MakeShared<TArray<uint8>>();
                    Value->Append(ResponseBody);
                    *Result = Value;
                }
                return nullptr;
            },
            nullptr
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            Future->EnsureCompletion();
            return Future->GetTask().Error();
        }
        Future->EnsureCompletion();
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FEzDataObjectDomain::FDownloadTask>> FEzDataObjectDomain::Download(
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FDownloadTask>>(
            this->AsShared()
        );
    }
}
