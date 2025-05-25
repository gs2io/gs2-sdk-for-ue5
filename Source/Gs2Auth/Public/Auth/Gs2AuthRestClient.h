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
#include "Core/Net/AbstractGs2Client.h"
#include "Request/LoginRequest.h"
#include "Task/Rest/LoginTask.h"
#include "Request/LoginBySignatureRequest.h"
#include "Task/Rest/LoginBySignatureTask.h"
#include "Request/FederationRequest.h"
#include "Task/Rest/FederationTask.h"
#include "Request/IssueTimeOffsetTokenByUserIdRequest.h"
#include "Task/Rest/IssueTimeOffsetTokenByUserIdTask.h"
#include "Request/GetServiceVersionRequest.h"
#include "Task/Rest/GetServiceVersionTask.h"

namespace Gs2::Auth
{
    class GS2AUTH_API FGs2AuthRestClient : Core::Net::FAbstractGs2Client
    {
    public:
        explicit FGs2AuthRestClient(
            const Core::Net::Rest::FGs2RestSessionPtr Session
        ): FAbstractGs2Client(Session)
        {
        }

        TSharedPtr<FAsyncTask<Task::Rest::FLoginTask>> Login(
            const Request::FLoginRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FLoginBySignatureTask>> LoginBySignature(
            const Request::FLoginBySignatureRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FFederationTask>> Federation(
            const Request::FFederationRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FIssueTimeOffsetTokenByUserIdTask>> IssueTimeOffsetTokenByUserId(
            const Request::FIssueTimeOffsetTokenByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetServiceVersionTask>> GetServiceVersion(
            const Request::FGetServiceVersionRequestPtr Request
        ) const;
    };
    typedef TSharedPtr<FGs2AuthRestClient, ESPMode::ThreadSafe> FGs2AuthRestClientPtr;
}