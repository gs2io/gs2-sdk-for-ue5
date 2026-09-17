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


#include "Gs2Constant.h"

#include "Core/Net/Steady.h"

DEFINE_LOG_CATEGORY(Gs2Log);

namespace Gs2::Core
{
    const FString FGs2Constant::DefaultEndpointHost = "https://{service}.{region}.gen2.gs2io.com";
    const FString FGs2Constant::DefaultWebSocketEndpointHost = "wss://gateway-ws.{region}.gen2.gs2io.com/v2";

    FString FGs2Constant::EndpointHost = FGs2Constant::DefaultEndpointHost;
    FString FGs2Constant::WebSocketEndpointHost = FGs2Constant::DefaultWebSocketEndpointHost;

    FString FGs2Constant::SteadyAppliedEndpointHost = FString();

    bool FGs2Constant::IsEndpointHostOverridden()
    {
        return EndpointHost != DefaultEndpointHost && EndpointHost != SteadyAppliedEndpointHost;
    }

    void FGs2Constant::ApplySteadyEndpointHost(const FString& SteadyEndpoint)
    {
        if (IsEndpointHostOverridden())
        {
            // アプリが自分で template を入れている。静的な上書きは Steady より強い。
            return;
        }
        const auto Template = Net::FGs2Steady::RestTemplate(SteadyEndpoint);
        EndpointHost = Template.IsEmpty() ? DefaultEndpointHost : Template;
        SteadyAppliedEndpointHost = Template;
    }
}